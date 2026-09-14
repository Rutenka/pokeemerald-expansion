#!/usr/bin/env python3
"""
Static validator for this project's custom maps - checks the failure classes
that have actually caused real, repeated bugs here (see CLAUDE.md's
world-building checklist), by reading map.json/layouts.json/tileset data
directly. No build, no emulator - meant to run in a few seconds before ever
calling a map "ready," per the interview-agreed verification ladder (this is
step 0, before Porymap, before mGBA).

Checks implemented, each tied to a real bug this project has actually hit:
  - Dangling warp targets: dest_map doesn't exist, or dest_warp_id is out of
    range for the destination map's own warp_events (checklist background;
    never actually hit, but foundational and cheap).
  - A coord_event sitting on the exact tile of a warp_events landing spot -
    step-based triggers don't reliably fire on a tile the player arrives at
    via warp, not a step (Thirteenth/Fifteenth feature entries: the "no
    garden" bug, the estate-grounds narration bug).
  - Half-wired two-tile doors: a door-behavior metatile with a warp, whose
    horizontal neighbor is ALSO a door-behavior metatile but has no warp
    (Tenth/Eleventh feature entries: two separate real doors shipped with
    only one side wired).
  - Suspicious elevation-0 ground: a walkable, non-water outdoor tile at
    elevation 0 (ELEVATION_TRANSITION, a collision-mismatch wildcard) that
    isn't near any warp/coord_event - almost always a hand-patching mistake,
    not intentional (Tenth/Eleventh feature entries: the walk-on-water bug).
  - Map connection collision continuity: for every declared `connections`
    entry, walks the whole shared edge (using the real FillConnection offset
    formula from src/fieldmap.c) and flags any tile pair where one side is
    walkable and the other is solid (Ninth feature entry: the garden/road
    seam saga - this is the single most expensive bug class this project has
    hit, three separate times before connections were mostly abandoned).

Usage:
    python3 tools/validate_maps.py                  # every Wasteland_* map
    python3 tools/validate_maps.py Wasteland_Road    # just this one (repeatable)

Exit code 0 if no errors (warnings are non-fatal, printed anyway); 1 if any
error was found on any checked map.
"""
import glob
import json
import os
import re
import sys

REPO = os.path.expanduser("~/Projects/pokemon-wasteland")
MAPS_DIR = os.path.join(REPO, "data/maps")
LAYOUTS_JSON = os.path.join(REPO, "data/layouts/layouts.json")
PRIMARY_TILESETS_DIR = os.path.join(REPO, "data/tilesets/primary")
SECONDARY_TILESETS_DIR = os.path.join(REPO, "data/tilesets/secondary")
BEHAVIORS_HEADER = os.path.join(REPO, "include/constants/metatile_behaviors.h")

NUM_TILES_IN_PRIMARY = 512
# Vanilla/Emerald-mode 16-bit metatile attribute layout (confirmed against
# include/global.fieldmap.h - this project uses the 2-byte-per-entry format,
# not the FRLG 4-byte one): behavior in bits 0-7, layer type in bits 12-15.
METATILE_ATTR_BEHAVIOR_MASK = 0x00FF

# Real vanilla tileset directory names are the snake_case form of the
# gTileset_X symbol with its prefix stripped (gTileset_General -> "general",
# gTileset_GenericBuilding -> "generic_building", gTileset_RusturfTunnel ->
# "rusturf_tunnel") - confirmed against every tileset directory actually
# used by this project so far, including the multi-word ones.
def tileset_dir_name(symbol):
    name = symbol.removeprefix("gTileset_")
    return re.sub(r"(?<!^)(?=[A-Z])", "_", name).lower()


def load_behavior_indices():
    """Parse the plain sequential enum in metatile_behaviors.h into a
    name -> index dict, since the .h file is the only source of truth for
    which numeric value each MB_* name has, and there's no JSON export of it."""
    text = open(BEHAVIORS_HEADER).read()
    body = re.search(r"enum\s*{(.*?)};", text, re.S).group(1)
    names = []
    for line in body.splitlines():
        line = line.split("//")[0].strip().rstrip(",")
        if not line:
            continue
        assert "=" not in line, f"unexpected explicit enum value: {line!r}"
        names.append(line)
    return {name: i for i, name in enumerate(names)}


BEHAVIORS = load_behavior_indices()
DOOR_BEHAVIORS = {BEHAVIORS["MB_NON_ANIMATED_DOOR"], BEHAVIORS["MB_ANIMATED_DOOR"]}
# Every metatile behavior that actually causes a passive warp_events entry to
# fire on its own via ordinary walking (TryDoorWarp, ForcedMovement_Warp*,
# stairs, etc.) - a warp_events array entry with NONE of these on its own
# tile, and no coord_event at the same coordinate either, is real destination
# *data* that nothing ever invokes (see check_warp_has_trigger below and the
# Twenty-ninth feature entry's real, shipped bug: Rustboro's return warp sat
# on plain MB_NORMAL ground and simply never fired on foot).
WARP_TRIGGER_BEHAVIORS = DOOR_BEHAVIORS | {
    b for name, b in BEHAVIORS.items()
    if name in (
        "MB_NORTH_ARROW_WARP", "MB_SOUTH_ARROW_WARP", "MB_EAST_ARROW_WARP", "MB_WEST_ARROW_WARP",
        "MB_WATER_SOUTH_ARROW_WARP", "MB_DEEP_SOUTH_WARP",
        "MB_AQUA_HIDEOUT_WARP", "MB_LAVARIDGE_GYM_1F_WARP", "MB_LAVARIDGE_GYM_B1F_WARP",
        "MB_BATTLE_PYRAMID_WARP", "MB_MOSSDEEP_GYM_WARP",
        "MB_UP_RIGHT_STAIR_WARP", "MB_UP_LEFT_STAIR_WARP", "MB_DOWN_RIGHT_STAIR_WARP", "MB_DOWN_LEFT_STAIR_WARP",
        "MB_STAIRS_OUTSIDE_ABANDONED_SHIP", "MB_ROCK_STAIRS",
        "MB_WATERFALL", "MB_ASHGROVE_LADDER",
    )
}
WATER_BEHAVIORS = {
    BEHAVIORS[name]
    for name in (
        "MB_POND_WATER", "MB_INTERIOR_DEEP_WATER", "MB_DEEP_WATER", "MB_WATERFALL",
        "MB_SOOTOPOLIS_DEEP_WATER", "MB_OCEAN_WATER", "MB_PUDDLE", "MB_SHALLOW_WATER",
        "MB_UNUSED_SOOTOPOLIS_DEEP_WATER", "MB_NO_SURFACING",
    )
    if name in BEHAVIORS
}

_layouts_cache = None
_maps_index_cache = None


def load_layouts():
    global _layouts_cache
    if _layouts_cache is None:
        _layouts_cache = {l["id"]: l for l in json.load(open(LAYOUTS_JSON))["layouts"]}
    return _layouts_cache


def load_maps_index():
    """id -> (map.json dict, directory) for every map in the whole repo, not
    just Wasteland_* ones - a warp or connection can legitimately point at a
    vanilla map, so dangling-reference checks need the full universe."""
    global _maps_index_cache
    if _maps_index_cache is None:
        index = {}
        for path in glob.glob(os.path.join(MAPS_DIR, "**/map.json"), recursive=True):
            d = json.load(open(path))
            index[d["id"]] = (d, os.path.dirname(path))
        _maps_index_cache = index
    return _maps_index_cache


class TilesetAttrs:
    """Lazily-loaded, cached metatile_attributes.bin reader for one
    primary+secondary tileset pair, giving behavior-by-global-metatile-id."""

    _cache = {}

    def __init__(self, primary_symbol, secondary_symbol):
        key = (primary_symbol, secondary_symbol)
        if key in TilesetAttrs._cache:
            self.__dict__ = TilesetAttrs._cache[key].__dict__
            return
        p_path = os.path.join(PRIMARY_TILESETS_DIR, tileset_dir_name(primary_symbol), "metatile_attributes.bin")
        s_path = os.path.join(SECONDARY_TILESETS_DIR, tileset_dir_name(secondary_symbol), "metatile_attributes.bin")
        self.primary = open(p_path, "rb").read()
        self.secondary = open(s_path, "rb").read()
        TilesetAttrs._cache[key] = self

    def behavior(self, metatile_id):
        if metatile_id >= NUM_TILES_IN_PRIMARY:
            data, idx = self.secondary, metatile_id - NUM_TILES_IN_PRIMARY
        else:
            data, idx = self.primary, metatile_id
        off = idx * 2
        if off + 2 > len(data):
            return None  # out-of-range metatile id - a different, real bug, but not this script's concern
        raw = data[off] | (data[off + 1] << 8)
        return raw & METATILE_ATTR_BEHAVIOR_MASK


def load_grid(layout):
    """width x height grid of (metatile_id, collision, elevation) tuples."""
    w, h = layout["width"], layout["height"]
    data = open(os.path.join(REPO, layout["blockdata_filepath"]), "rb").read()
    assert len(data) == w * h * 2, f"{layout['id']}: expected {w*h*2} bytes, got {len(data)}"
    grid = []
    for y in range(h):
        row = []
        for x in range(w):
            i = (y * w + x) * 2
            raw = data[i] | (data[i + 1] << 8)
            row.append((raw & 0x3FF, (raw >> 10) & 3, (raw >> 12) & 0xF))
        grid.append(row)
    return grid


def warp_id_valid(dest_map_id, dest_warp_id, maps_index):
    if dest_warp_id in ("-1", -1):
        return True, None  # dynamic/none - not this script's concern
    if dest_map_id not in maps_index:
        return False, f"dest_map {dest_map_id} does not exist"
    dest_json, _ = maps_index[dest_map_id]
    count = len(dest_json.get("warp_events", []))
    idx = int(dest_warp_id)
    if not (0 <= idx < count):
        return False, f"dest_warp_id {idx} out of range for {dest_map_id} (has {count} warp_events)"
    return True, None


def check_warps(map_json, maps_index, errors):
    for i, w in enumerate(map_json.get("warp_events", [])):
        ok, msg = warp_id_valid(w["dest_map"], w["dest_warp_id"], maps_index)
        if not ok:
            errors.append(f"warp_events[{i}] at ({w['x']},{w['y']}): {msg}")


def check_coord_event_on_landing_tile(map_json, warnings):
    # Downgraded from an error to a warning (2026-09-14): a coord_event on a
    # landing tile is the Thirteenth/Fifteenth feature entries' real bug
    # class ONLY if the script is meant to fire on/soon after arrival (e.g.
    # arrival narration) - warps arriving there don't count as a "step", so
    # it silently never fires. But the Twenty-ninth feature entry found a
    # second, legitimate use of this exact same property: an *outbound* exit
    # trigger deliberately placed on a landing tile, specifically so it does
    # NOT fire on arrival (no step taken) and only fires later, when a
    # player genuinely walks back onto that tile to leave. This check can't
    # tell those two cases apart from the data alone - flag it, but verify
    # by intent (is this script supposed to run right after arriving, or
    # only when the player deliberately returns here?) before assuming it's
    # broken.
    warp_coords = {(w["x"], w["y"]) for w in map_json.get("warp_events", [])}
    for i, ce in enumerate(map_json.get("coord_events", [])):
        if (ce["x"], ce["y"]) in warp_coords:
            warnings.append(
                f"coord_events[{i}] at ({ce['x']},{ce['y']}) sits exactly on a warp's landing "
                f"tile - a step-based trigger here silently never fires on arrival (warping in "
                f"isn't a 'step'), only on a later genuine step onto the same tile. Broken if "
                f"this is meant to run right after arriving (e.g. narration - see checklist item "
                f"6 / the Thirteenth and Fifteenth feature entries); correct and intentional if "
                f"this is an outbound exit trigger that should only fire when a player "
                f"deliberately walks back here to leave (see the Twenty-ninth feature entry)."
            )


def check_doors(map_json, layout, attrs, errors, warnings):
    w, h = layout["width"], layout["height"]
    grid = load_grid(layout)
    door_tiles = set()
    for y in range(h):
        for x in range(w):
            behavior = attrs.behavior(grid[y][x][0])
            if behavior in DOOR_BEHAVIORS:
                door_tiles.add((x, y))
    warp_at = {(w_["x"], w_["y"]) for w_ in map_json.get("warp_events", [])}
    for (x, y) in sorted(door_tiles):
        if (x, y) not in warp_at:
            warnings.append(
                f"door-behavior metatile at ({x},{y}) has no warp_events entry - "
                f"intentional (a locked/decorative door) or a missing warp?"
            )
            continue
        for nx in (x - 1, x + 1):
            if (nx, y) in door_tiles and (nx, y) not in warp_at:
                errors.append(
                    f"possible half-wired two-tile door: ({x},{y}) has a warp, but its "
                    f"neighboring door-behavior tile ({nx},{y}) does not - a real door's other "
                    f"half is usually a second warp_events entry, not just tile art (checklist "
                    f"item 9 / the Tenth and Eleventh feature entries)."
                )


def check_elevation_zero(map_json, layout, attrs, errors, warnings):
    if map_json.get("map_type") not in ("MAP_TYPE_ROUTE", "MAP_TYPE_TOWN"):
        return
    w, h = layout["width"], layout["height"]
    grid = load_grid(layout)
    event_coords = {(e["x"], e["y"]) for e in map_json.get("warp_events", [])}
    event_coords |= {(e["x"], e["y"]) for e in map_json.get("coord_events", [])}

    def near_event(x, y):
        return any((x + dx, y + dy) in event_coords for dx in (-1, 0, 1) for dy in (-1, 0, 1))

    suspicious = []
    for y in range(h):
        for x in range(w):
            metatile, collision, elevation = grid[y][x]
            if collision != 0 or elevation != 0:
                continue
            behavior = attrs.behavior(metatile)
            if behavior in WATER_BEHAVIORS:
                continue  # water's own tiles are frequently elevation 0-adjacent by design
            if near_event(x, y):
                continue  # legitimate ELEVATION_TRANSITION wildcard use (checklist item 5)
            suspicious.append((x, y))
    if suspicious:
        preview = ", ".join(f"({x},{y})" for x, y in suspicious[:8])
        more = f" (+{len(suspicious) - 8} more)" if len(suspicious) > 8 else ""
        warnings.append(
            f"{len(suspicious)} walkable outdoor tile(s) at elevation 0 with no nearby "
            f"warp/coord_event: {preview}{more} - elevation 0 is ELEVATION_TRANSITION, a "
            f"wildcard that can silently defeat water-crossing collision checks if it's on "
            f"ordinary hand-patched ground rather than intentional (checklist item 10 / the "
            f"Tenth feature entry's walk-on-water bug). Ordinary outdoor ground should almost "
            f"always be elevation 3."
        )


def check_event_tiles_walkable(map_json, layout, attrs, errors):
    """Every warp_events and coord_events coordinate on THIS map must itself be
    collision-open in the current tile data. This exists specifically because a
    hand-patch that overwrites a region of a map's raw .bin data (e.g. pasting in
    a rock formation) can silently turn a warp's landing tile, a door tile, or a
    coord_event trigger tile solid without anyone noticing - the previous version
    of this validator only checked whether events pointed at valid destinations
    and metatile *behavior*, never whether the *collision* at an event's own
    coordinate was still 0. This is exactly the class of bug that trapped a
    player right outside Wasteland_EstateHouse's door (2026-09-13): a new rock
    formation was pasted over the mansion door's own landing tile and the
    arrival-narration coord_event's tile, both silently made solid, and nothing
    caught it before a real playtest did. Run this after ANY hand-patch to a
    map's raw tile bytes, not just when adding a new warp - it's cheap and
    covers every event already on the map, not just the one being worked on.
    """
    w, h = layout["width"], layout["height"]
    grid = load_grid(layout)

    def is_blocked(x, y):
        if not (0 <= x < w and 0 <= y < h):
            return False  # out of bounds isn't this check's concern
        _, collision, _ = grid[y][x]
        return collision != 0

    for i, wv in enumerate(map_json.get("warp_events", [])):
        x, y = wv["x"], wv["y"]
        if 0 <= x < w and 0 <= y < h and attrs.behavior(grid[y][x][0]) in DOOR_BEHAVIORS:
            continue  # real doors routinely have collision=1 on their own tile art -
                      # TryDoorWarp's door-behavior check bypasses ordinary collision,
                      # so this is normal, not a sign anything was overwritten.
        if is_blocked(x, y):
            errors.append(
                f"warp_events[{i}] at ({x},{y}) sits on a collision-blocked tile - "
                f"a hand-patch likely overwrote this warp's own tile with solid "
                f"terrain. The warp itself may still fire, but check whether the "
                f"player can actually stand here / walk away afterward."
            )
    for i, ce in enumerate(map_json.get("coord_events", [])):
        x, y = ce["x"], ce["y"]
        if is_blocked(x, y):
            errors.append(
                f"coord_events[{i}] at ({x},{y}) sits on a collision-blocked tile - "
                f"this trigger can never fire (the player can never step onto it), "
                f"and a hand-patch likely overwrote it with solid terrain."
            )


def check_warp_has_trigger(map_json, layout, attrs, warnings):
    """A warp_events entry is only destination *data* - it does nothing on
    its own unless something actually invokes it: either the tile it sits on
    has a real passive warp-triggering behavior (a door, an arrow-warp,
    stairs, ...), or a coord_event at that same coordinate runs an explicit
    `warp`/`warpdoor` script command. A warp_events entry on plain ground
    with neither is silent, permanently-dead data - it will never fire no
    matter how a player approaches it, and (this is what makes it dangerous)
    it still looks completely correct in every other check: valid
    destination, open collision, no elevation mismatch. Confirmed as a real,
    shipped bug 2026-09-14: Rustboro's return warp to the corporate
    checkpoint sat on plain MB_NORMAL ground with no coord_event, and simply
    never fired for a real player, despite passing every other check this
    file already had. Only warp_events entries that are the *reciprocal
    landing target* of some other map's real door are exempt from needing
    their own trigger (a landing coordinate is written to purely for warps
    arriving *into* it - it isn't itself expected to fire outbound), so this
    check cannot tell a genuinely-dead entry apart from a landing-only one
    just from this map's own data. Reported as a warning, not an error, for
    that reason - but treat every one of these as a real "does the return
    trip actually work" question to check, not a false positive to ignore.
    """
    w, h = layout["width"], layout["height"]
    grid = load_grid(layout)
    coord_event_coords = {(ce["x"], ce["y"]) for ce in map_json.get("coord_events", [])}

    for i, wv in enumerate(map_json.get("warp_events", [])):
        x, y = wv["x"], wv["y"]
        if not (0 <= x < w and 0 <= y < h):
            continue
        behavior = attrs.behavior(grid[y][x][0])
        if behavior in WARP_TRIGGER_BEHAVIORS:
            continue
        if (x, y) in coord_event_coords:
            continue
        warnings.append(
            f"warp_events[{i}] at ({x},{y}) sits on plain ground (metatile behavior "
            f"has no passive warp trigger) with no coord_event at the same "
            f"coordinate either - if this is meant to fire outbound (not just serve "
            f"as a landing target for warps arriving here), it never will. Add a "
            f"coord_event + `warp`/`warpdoor` script command, or confirm this is "
            f"landing-only."
        )


def check_connections(name, map_json, maps_index, errors, warnings):
    layouts = load_layouts()
    connections = map_json.get("connections") or []
    for conn in connections:
        other_id = conn["map"]
        if other_id not in maps_index:
            errors.append(f"connection to {other_id} ({conn['direction']}): map does not exist")
            continue
        other_json, _ = maps_index[other_id]
        layout_a = layouts[map_json["layout"]]
        layout_b = layouts[other_json["layout"]]
        attrs_a = TilesetAttrs(layout_a["primary_tileset"], layout_a["secondary_tileset"])
        attrs_b = TilesetAttrs(layout_b["primary_tileset"], layout_b["secondary_tileset"])
        grid_a = load_grid(layout_a)
        grid_b = load_grid(layout_b)
        offset = conn["offset"]
        direction = conn["direction"]
        wa, ha = layout_a["width"], layout_a["height"]
        wb, hb = layout_b["width"], layout_b["height"]

        # Real FillConnection formula from src/fieldmap.c: north/south shift
        # the column index by -offset, east/west shift the row index by
        # -offset (documented in CLAUDE.md's checklist item 4, re-derived
        # here for east/west from the source's FillWestConnection/
        # FillEastConnection symmetry with FillNorthConnection/FillSouthConnection).
        mismatches = []
        if direction in ("up", "down"):
            edge_y_a = 0 if direction == "up" else ha - 1
            edge_y_b = hb - 1 if direction == "up" else 0
            for xa in range(wa):
                xb = xa - offset
                if not (0 <= xb < wb):
                    continue
                _, coll_a, _ = grid_a[edge_y_a][xa]
                _, coll_b, _ = grid_b[edge_y_b][xb]
                if (coll_a == 0) != (coll_b == 0):
                    mismatches.append((xa, edge_y_a, xb, edge_y_b))
        elif direction in ("left", "right"):
            edge_x_a = 0 if direction == "left" else wa - 1
            edge_x_b = wb - 1 if direction == "left" else 0
            for ya in range(ha):
                yb = ya - offset
                if not (0 <= yb < hb):
                    continue
                _, coll_a, _ = grid_a[ya][edge_x_a]
                _, coll_b, _ = grid_b[yb][edge_x_b]
                if (coll_a == 0) != (coll_b == 0):
                    mismatches.append((edge_x_a, ya, edge_x_b, yb))
        else:
            warnings.append(f"connection direction {direction!r} not handled by this validator yet")
            continue

        if mismatches:
            preview = ", ".join(f"{name}({ax},{ay})<->{other_id}({bx},{by})" for ax, ay, bx, by in mismatches[:6])
            more = f" (+{len(mismatches) - 6} more)" if len(mismatches) > 6 else ""
            # Deliberately a warning, not an error: collision asymmetry across a
            # seam is often completely normal (an open route ending at a town's
            # solid building wall is fine and correctly blocks the player) -
            # this can't tell "correctly rendered wall" apart from "looks open
            # but isn't" without actually looking at the tile art, which is
            # exactly why checklist item 13 says a data check alone isn't
            # sufficient. Use this as a shortlist of exactly which coordinates
            # to render with tileset_preview.py --map or check in-game, not as
            # a verdict on its own.
            warnings.append(
                f"connection {direction} to {other_id} (offset {offset}): "
                f"{len(mismatches)} tile pair(s) with mismatched walkability across the seam "
                f"(collision-only heuristic - many of these are normal, e.g. open ground "
                f"meeting a solid building wall): {preview}{more}. Worth a look ONLY if the "
                f"open side's tile art doesn't visually read as solid (checklist item 2/4/13 - "
                f"the Ninth feature entry's garden/road seam saga was exactly this: a tile that "
                f"looked open but wasn't, not just any asymmetry)."
            )


def validate_one(name, maps_index):
    map_dir = os.path.join(MAPS_DIR, name)
    map_json_path = os.path.join(map_dir, "map.json")
    if not os.path.exists(map_json_path):
        return [f"{name}: no map.json found at {map_json_path}"], []
    map_json = json.load(open(map_json_path))
    layouts = load_layouts()
    layout = layouts.get(map_json["layout"])
    errors, warnings = [], []
    if layout is None:
        errors.append(f"layout {map_json['layout']} not found in layouts.json")
        return errors, warnings
    attrs = TilesetAttrs(layout["primary_tileset"], layout["secondary_tileset"])

    check_warps(map_json, maps_index, errors)
    check_coord_event_on_landing_tile(map_json, warnings)
    check_doors(map_json, layout, attrs, errors, warnings)
    check_elevation_zero(map_json, layout, attrs, errors, warnings)
    check_event_tiles_walkable(map_json, layout, attrs, errors)
    check_warp_has_trigger(map_json, layout, attrs, warnings)
    check_connections(name, map_json, maps_index, errors, warnings)
    return errors, warnings


def main():
    requested = sys.argv[1:]
    maps_index = load_maps_index()
    if requested:
        names = requested
    else:
        names = sorted(
            os.path.basename(p) for p in glob.glob(os.path.join(MAPS_DIR, "Wasteland_*")) if os.path.isdir(p)
        )

    any_errors = False
    for name in names:
        errors, warnings = validate_one(name, maps_index)
        if not errors and not warnings:
            print(f"[OK] {name}")
            continue
        print(f"[{'FAIL' if errors else 'WARN'}] {name}")
        for e in errors:
            print(f"    ERROR: {e}")
        for w in warnings:
            print(f"    warning: {w}")
        any_errors = any_errors or bool(errors)

    sys.exit(1 if any_errors else 0)


if __name__ == "__main__":
    main()
