"""
Headless mGBA driver for pokemon-wasteland, using mgba's Python bindings.

Lets us script the emulator directly (press buttons, step frames, read/write
save-block memory) instead of asking Viktor to test every small change by hand.

Usage as a library: import and use MgbaSession. Run directly for a smoke test.
"""
import os
import sys

MGBA_PYLIB = os.path.expanduser("~/Projects/mgba/build/python/lib.linux-x86_64-cpython-312")
sys.path.insert(0, MGBA_PYLIB)

import mgba.log  # noqa: E402
import mgba.core  # noqa: E402
import mgba.gba  # noqa: E402
import mgba.image  # noqa: E402

ROM_PATH = os.path.expanduser("~/Projects/pokemon-wasteland/pokeemerald.gba")
MAP_PATH = os.path.expanduser("~/Projects/pokemon-wasteland/pokeemerald.map")

# Every symbol address used below is re-derived from pokeemerald.map at import
# time instead of hardcoded: a normal vs. DEBUG=1 build (or just enough
# unrelated code changing) reflows the linker's layout and silently breaks
# hardcoded addresses - this bit us once already (see git history / session
# notes) when a DEBUG build's CB2_Overworld etc. landed at different addresses
# than the normal build's.
_SYMBOL_NAMES = (
    "gSaveBlock1Ptr", "gSaveBlock2Ptr", "gMain",
    "CB2_Overworld", "CB2_ContinueSavedGame", "CB2_InitMainMenu",
)


def _load_symbols(map_path, names):
    wanted = set(names)
    found = {}
    with open(map_path) as f:
        for line in f:
            parts = line.split()
            if len(parts) == 2 and parts[1] in wanted and parts[0].startswith("0x"):
                found[parts[1]] = int(parts[0], 16)
    missing = wanted - found.keys()
    if missing:
        raise RuntimeError(f"symbols not found in {map_path}: {missing}")
    return found


_SYM = _load_symbols(MAP_PATH, _SYMBOL_NAMES)

ADDR_SAVEBLOCK1_PTR = _SYM["gSaveBlock1Ptr"]
ADDR_SAVEBLOCK2_PTR = _SYM["gSaveBlock2Ptr"]

# struct Main (include/main.h): callback2 is the currently active "screen"
# function (title screen, main menu, overworld, ...). callback2 is the
# second word (offset 0x04) of gMain.
ADDR_GMAIN = _SYM["gMain"]
GMAIN_CALLBACK2_OFFSET = 0x04

# Compared with the low bit masked off, since Thumb-mode function pointers
# get that bit set (BX-selects Thumb) but ARM-mode ones don't.
CB2_OVERWORLD_ADDR = _SYM["CB2_Overworld"]
CB2_CONTINUE_SAVED_GAME_ADDR = _SYM["CB2_ContinueSavedGame"]
CB2_INIT_MAIN_MENU_ADDR = _SYM["CB2_InitMainMenu"]

# Offsets within struct SaveBlock1 (include/global.h)
SB1_POS = 0x00          # struct Coords16 { s16 x, y }
SB1_LOCATION = 0x04      # struct WarpData { s8 mapGroup, mapNum; u8 warpId; s16 x, y }
SB1_FLAGS = 0x1270
SB1_VARS = 0x139C

NUM_FLAG_BYTES = 0x12C   # (0x139C - 0x1270), matches NUM_FLAG_BYTES at build time


class MgbaSession:
    def __init__(self, rom_path=ROM_PATH, silence_logs=True):
        if silence_logs:
            self._silence_native_logs()
        self.core = mgba.core.load_path(rom_path)
        if self.core is None:
            raise RuntimeError(f"failed to load ROM: {rom_path}")
        self.core.autoload_save()
        # set_video_buffer must be called BEFORE reset() (confirmed against
        # mgba's own cinema/movie.py) - the other order silently leaves the
        # buffer all-zero forever, no error, nothing rendered into it ever.
        w, h = self.core.desired_video_dimensions()
        self._video_image = mgba.image.Image(w, h)
        self.core.set_video_buffer(self._video_image)
        self.core.reset()

    @staticmethod
    def _silence_native_logs():
        # mgba.log.silence() itself crashes (cffi can't marshal va_list in
        # the log callback), so just redirect the fd mgba's C logger writes
        # to (fd 1 - confirmed empirically, not fd 2) instead of using its
        # Python logging override. Deliberately leaves fd 2/sys.stderr alone
        # so Python tracebacks stay visible - silencing both fds once made a
        # real exception here disappear into a bare "exit code 1".
        os.dup2(1, 3)
        devnull = os.open(os.devnull, os.O_WRONLY)
        os.dup2(devnull, 1)
        sys.stdout = os.fdopen(3, "w")

    # --- memory helpers -------------------------------------------------

    def _read_ptr(self, addr):
        mem = self.core.memory.u32
        return mem[addr]

    def saveblock1_addr(self):
        return self._read_ptr(ADDR_SAVEBLOCK1_PTR)

    def saveblock2_addr(self):
        return self._read_ptr(ADDR_SAVEBLOCK2_PTR)

    def get_pos(self):
        base = self.saveblock1_addr()
        mem16 = self.core.memory.u16
        x = mem16[base + SB1_POS]
        y = mem16[base + SB1_POS + 2]
        return x, y

    def get_location(self):
        base = self.saveblock1_addr()
        mem8 = self.core.memory.u8
        map_group = mem8[base + SB1_LOCATION]
        map_num = mem8[base + SB1_LOCATION + 1]
        warp_id = mem8[base + SB1_LOCATION + 2]
        return map_group, map_num, warp_id

    def get_flag(self, flag_id):
        base = self.saveblock1_addr()
        mem8 = self.core.memory.u8
        byte = mem8[base + SB1_FLAGS + (flag_id // 8)]
        return bool(byte & (1 << (flag_id % 8)))

    def set_flag(self, flag_id, value=True):
        base = self.saveblock1_addr()
        mem8 = self.core.memory.u8
        addr = base + SB1_FLAGS + (flag_id // 8)
        byte = mem8[addr]
        if value:
            byte |= (1 << (flag_id % 8))
        else:
            byte &= ~(1 << (flag_id % 8))
        mem8[addr] = byte

    def get_var(self, var_offset_index):
        base = self.saveblock1_addr()
        mem16 = self.core.memory.u16
        return mem16[base + SB1_VARS + var_offset_index * 2]

    def get_callback2(self):
        """Current gMain.callback2, with the Thumb low bit masked off so it
        compares cleanly against a plain function address from the map file."""
        mem32 = self.core.memory.u32
        return mem32[ADDR_GMAIN + GMAIN_CALLBACK2_OFFSET] & ~1

    def is_in_overworld(self):
        return self.get_callback2() == CB2_OVERWORLD_ADDR

    # --- input helpers ----------------------------------------------------

    def press(self, *keys, frames=1, hold_frames=10):
        # mgba's Core.set_keys(*keys)/clear_keys(*keys) each take keys as
        # SEPARATE positional args and do `1 << key` internally per arg
        # (see mgba/core.py's _keys_to_int) - the GBA.KEY_* constants are
        # plain bit-position numbers (KEY_A=0, KEY_START=3, KEY_R=8, ...),
        # not pre-shifted bitmask values. Pre-OR'ing them together first
        # (the original bug here) silently produces a nonsense combined
        # "key" that gets misinterpreted as a single huge bit-shift -
        # single-key presses happened to work by coincidence (OR of one
        # value is a no-op), which is exactly why this went unnoticed until
        # the first real multi-key combo (R+START for the debug menu).
        self.core.set_keys(*keys)
        for _ in range(hold_frames):
            self.core.run_frame()
        self.core.clear_keys(*keys)
        for _ in range(frames):
            self.core.run_frame()

    def run_frames(self, n):
        for _ in range(n):
            self.core.run_frame()

    def boot_to_overworld(self, log=False):
        """Drive the boot sequence (copyright/logos -> ~5400-frame title
        animation -> interactive title screen -> main menu -> Continue) into
        actual overworld control, using a save that already exists on disk.

        Real, empirically-measured timing (2026-09-12), not a guess: from a
        cold boot it takes roughly 5400 emulated frames (copyright screen,
        PRET x RHH splash, GAME FREAK logo, then Emerald's own multi-stage
        title animation - landscape scene, Rayquaza reveal, logo shatter) to
        reach the actual interactive "PRESS START" title screen. This matters
        because the previous version of this method started mashing A after
        only 120 frames - deep inside that long non-interactive animation -
        which sometimes accidentally advanced things far enough, and other
        times (confirmed via screenshots) drove the title screen into its own
        idle attract-mode demo loop instead of the real menu. That demo loop
        runs through the same CB2_Overworld callback as genuine gameplay (so
        is_in_overworld() reports True) and reads back a fixed, unrelated
        map/position - the fact that this ever looked like a working smoke
        test was a false positive, not a real fix. See CLAUDE.md's
        world-building checklist for why this is exactly the kind of thing a
        static/data-only check can't catch, but a real screenshot can.

        Only two presses are needed once we're actually at the interactive
        title screen: one to reach the main menu, one to select CONTINUE
        (always the first, pre-highlighted item whenever a valid save
        exists - confirmed via screenshot, not assumed). A few frames of
        margin are built into each wait; if a build's exact intro length
        ever drifts, re-verify with screenshots at each stage rather than
        guessing a new number.
        """
        self.run_frames(5400)
        self.press(mgba.gba.GBA.KEY_A, hold_frames=10, frames=60)
        self.run_frames(120)
        self.press(mgba.gba.GBA.KEY_A, hold_frames=10, frames=60)
        self.run_frames(120)
        reached = self.is_in_overworld()
        if log:
            print(f"boot_to_overworld: {'reached' if reached else 'FAILED to reach'} overworld")
        return reached

    def screenshot(self, path):
        self.core.run_frame()  # make sure the buffer holds a fully-rendered frame
        img = self._video_image.to_pil()
        img.convert("RGB").save(path)
        return path

    def save_state(self, path):
        # save_raw_state() returns raw cffi cdata, not a bytes object -
        # ffi.buffer(...) is needed to get something write() will accept.
        state = self.core.save_raw_state()
        with open(path, "wb") as f:
            f.write(bytes(mgba.core.ffi.buffer(state)))

    def load_state(self, path):
        with open(path, "rb") as f:
            self.core.load_raw_state(f.read())


if __name__ == "__main__":
    sess = MgbaSession()
    GBA = mgba.gba.GBA

    reached = sess.boot_to_overworld(log=True)
    print("reached overworld:", reached)
    print("callback2:", hex(sess.get_callback2()), "(CB2_Overworld =", hex(CB2_OVERWORLD_ADDR), ")")
    print("pos:", sess.get_pos())
    print("location (group, num, warp):", sess.get_location())
    print("FLAG_SYS_POKEMON_GET (0x860):", sess.get_flag(0x860))

    if reached:
        before = sess.get_pos()
        sess.press(GBA.KEY_UP, hold_frames=20, frames=20)
        after = sess.get_pos()
        print("pos before/after pressing UP:", before, "->", after)
        print("movement test:", "OK, position changed" if before != after else "NO CHANGE (blocked, or a wall to the north)")

    print("smoke test OK" if reached else "smoke test FAILED: did not reach overworld")
