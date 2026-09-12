"""
Closed-loop, BFS-based headless walking helper for tools/mgba_probe.py.

Built during the Twenty-first custom feature (Miller's Cut) after two real
failure modes with naive dead-reckoned press sequences:

1. A single "turn to face a new direction" press doesn't move the player -
   only the next press in that same direction does. A pre-computed sequence
   of presses has no way to know when a turn silently ate one of its steps,
   so every later press in the sequence ends up one tile off from where it
   assumed the player was. This module re-reads the player's real position
   after every single press and recomputes a fresh direction each time,
   which is immune to that drift by construction.

2. A "player position hasn't changed in N presses" symptom looks identical
   whether the cause is a real navigation problem (a wall, a one-way ledge)
   or a multi-page msgbox silently absorbing directional input as a no-op.
   Chasing the terrain explanation cost real time on Miller's Cut before a
   screenshot showed the arrival narration still open on page one - the
   under-mashing mistake checklist item 15 already warns about. This
   module's stuck-detection tries clearing a possible textbox with A first,
   escalating the number of presses across a couple of attempts, before
   concluding a real navigation failure - but a real screenshot is still the
   only way to be *sure* which one it is. Check one before trusting either
   "reached"/"stuck" as the final word on a genuinely new map.

Usage (import mgba_probe first - it puts mgba's Python bindings on sys.path,
which this module's own `import mgba.gba` needs):
    from mgba_probe import MgbaSession
    from smart_walk import smart_walk_to, load_full_grid

    grid = load_full_grid("data/layouts/SomeMap/map.bin", w, h,
                           "gTileset_General", "gTileset_Mauville")
    smart_walk_to(session, grid, w, h, target=(x, y), label="into town",
                   blocked_extra={(nx, ny) for each known NPC position})
"""
import mgba.gba as gba
from collections import deque
from validate_maps import TilesetAttrs, BEHAVIORS


def load_full_grid(map_bin_path, w, h, primary, secondary):
    """width x height grid of (collision, metatile_behavior) tuples."""
    data = open(map_bin_path, "rb").read()
    attrs = TilesetAttrs(primary, secondary)
    grid = []
    for y in range(h):
        row = []
        for x in range(w):
            i = (y * w + x) * 2
            raw = data[i] | (data[i + 1] << 8)
            mt = raw & 0x3FF
            coll = (raw >> 10) & 3
            row.append((coll, attrs.behavior(mt)))
        grid.append(row)
    return grid


# One-way ledges (src/field_player_avatar.c's ForcedMovement_WalkX / the
# sMetatileBehaviorFuncs table): only enterable when moving in the named
# direction - approaching from any other side is blocked exactly like a
# solid wall. MB_BUMPY_SLOPE/MB_MUDDY_SLOPE are deliberately NOT included
# here - they affect Acro Bike tricks and forced-slide movement respectively,
# not plain on-foot walkability.
LEDGE_DIR = {}
for _name, _dirn in [("MB_JUMP_SOUTH", "D"), ("MB_JUMP_NORTH", "U"),
                      ("MB_JUMP_EAST", "R"), ("MB_JUMP_WEST", "L")]:
    if _name in BEHAVIORS:
        LEDGE_DIR[BEHAVIORS[_name]] = _dirn


def bfs_next_dir(grid, w, h, blocked_extra, start, target):
    """The first step of a real shortest path from start to target, or None
    if none exists given the grid's collision/ledge data plus blocked_extra
    (a set of (x,y) tiles to treat as solid - use this for NPC object events,
    which block movement but aren't part of the static layout data)."""
    def can_enter(toxy, movedir):
        x, y = toxy
        if not (0 <= x < w and 0 <= y < h):
            return False
        if toxy in blocked_extra:
            return False
        coll, behavior = grid[y][x]
        if coll != 0:
            return False
        if behavior in LEDGE_DIR and LEDGE_DIR[behavior] != movedir:
            return False
        return True

    q = deque([start])
    prev = {start: None}
    while q:
        x, y = q.popleft()
        if (x, y) == target:
            break
        for dx, dy, name in ((0, -1, 'U'), (0, 1, 'D'), (-1, 0, 'L'), (1, 0, 'R')):
            nxt = (x + dx, y + dy)
            if can_enter(nxt, name) and nxt not in prev:
                prev[nxt] = ((x, y), name)
                q.append(nxt)
    if target not in prev:
        return None
    cur = target
    chain = []
    while prev[cur] is not None:
        pxy, name = prev[cur]
        chain.append((pxy, name))
        cur = pxy
    chain.reverse()
    return chain[0][1] if chain else None


K = gba.GBA
KEYMAP = {'U': K.KEY_UP, 'D': K.KEY_DOWN, 'L': K.KEY_LEFT, 'R': K.KEY_RIGHT}


def smart_walk_to(session, grid, w, h, target, max_steps=100, label="", blocked_extra=None):
    """Walk session's player toward target one real step at a time,
    recomputing the path from the actual current position every press.
    Returns "reached", "no_path", "left_overworld" (a script/battle took
    over - check is_in_overworld()/get_location() next), or "stuck" (still
    not moving after repeated attempts to clear a possible textbox - take a
    screenshot before assuming this means a real navigation problem)."""
    blocked_extra = blocked_extra or set()
    stuck_count = 0
    last_pos = None
    for i in range(max_steps):
        pos = session.get_pos()
        if pos == target:
            print(f"[{label}] reached target {target}")
            return "reached"
        if pos == last_pos:
            stuck_count += 1
        else:
            stuck_count = 0
        last_pos = pos
        if stuck_count in (2, 3):
            # Escalate: a 2-page msgbox needed ~40 presses to fully clear on
            # Miller's Cut - don't assume a fixed count is ever enough.
            mash_count = 20 * (stuck_count - 1)
            print(f"[{label}] stuck at {pos}, mashing A x{mash_count} to clear a possible textbox")
            for _ in range(mash_count):
                session.press(K.KEY_A, hold_frames=8, frames=20)
            continue
        if stuck_count >= 4:
            print(f"[{label}] still stuck at {pos} after repeated textbox-clear attempts - giving up")
            return "stuck"
        d = bfs_next_dir(grid, w, h, blocked_extra, pos, target)
        if d is None:
            print(f"[{label}] no path from {pos} to {target}")
            return "no_path"
        session.press(KEYMAP[d], hold_frames=10, frames=18)
        if not session.is_in_overworld():
            print(f"[{label}] left overworld at step {i}, pos was {pos}, pressed {d}")
            return "left_overworld"
    print(f"[{label}] max steps reached, pos={session.get_pos()}")
    return "max_steps"
