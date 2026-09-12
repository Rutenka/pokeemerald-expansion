"""
Renders a primary+secondary tileset pair into labeled metatile-grid PNGs, so
Claude (no GUI access to Porymap) can visually pick metatile IDs for hand-
authoring map layouts, the same way a human would use Porymap's tile picker.

Binary formats (metatiles.bin tile-entry bit layout, JASC-PAL palette files,
NUM_TILES_IN_PRIMARY=512/NUM_PALS_IN_PRIMARY=6) cross-checked against
~/Projects/porymap/src/core/tileset.cpp and include/fieldmap.h - this project
uses the Emerald (non-FRLG) constants and enable_triple_layer_metatiles=0
(2 layers x 4 tiles = 8 tile entries per metatile), per porymap.project.cfg.

Usage:
    python3 tools/tileset_preview.py <primary_name> <secondary_name> [out_dir]

e.g. python3 tools/tileset_preview.py building lab /tmp/preview
Produces <out_dir>/<primary>_metatiles.png and <out_dir>/<secondary>_metatiles.png,
each metatile labeled with its GLOBAL metatile ID (secondary IDs start at 512).
"""
import os
import sys
from PIL import Image, ImageDraw

REPO = os.path.expanduser("~/Projects/pokemon-wasteland")
TILE_SIZE = 8
METATILE_SIZE = 16
NUM_TILES_IN_PRIMARY = 512
NUM_PALS_IN_PRIMARY = 6
SCALE = 3  # upscale factor for readability
COLS = 16  # metatiles per row in the output grid


def load_pal(path):
    with open(path) as f:
        lines = f.read().splitlines()
    # JASC-PAL\n0100\n<count>\n<r g b>...
    colors = []
    for line in lines[3:19]:
        r, g, b = (int(x) for x in line.split())
        colors.append((r, g, b))
    return colors


def load_tileset_dir(path):
    tiles_im = Image.open(os.path.join(path, "tiles.png")).convert("P")
    palettes = [load_pal(os.path.join(path, "palettes", f"{i:02d}.pal")) for i in range(16)]
    with open(os.path.join(path, "metatiles.bin"), "rb") as f:
        metatile_data = f.read()
    with open(os.path.join(path, "metatile_attributes.bin"), "rb") as f:
        attr_data = f.read()
    return tiles_im, palettes, metatile_data, attr_data


def get_tile_indices(tiles_im, tile_id):
    """8x8 grid of raw palette-relative indices (0-15) for one tile."""
    cols = tiles_im.width // TILE_SIZE
    tx, ty = (tile_id % cols) * TILE_SIZE, (tile_id // cols) * TILE_SIZE
    px = tiles_im.load()
    return [[px[tx + x, ty + y] % 16 for x in range(TILE_SIZE)] for y in range(TILE_SIZE)]


def draw_tile(canvas, ox, oy, indices, palette, xflip, yflip):
    for y in range(TILE_SIZE):
        for x in range(TILE_SIZE):
            sx = TILE_SIZE - 1 - x if xflip else x
            sy = TILE_SIZE - 1 - y if yflip else y
            idx = indices[sy][sx]
            if idx == 0:
                continue  # palette index 0 = transparent (backdrop / see-through top layer)
            canvas.putpixel((ox + x, oy + y), palette[idx])


def render_metatile(entries, primary, secondary):
    """entries: list of 8 (tileId, xflip, yflip, palette) tuples (4 bottom, 4 top)."""
    canvas = Image.new("RGB", (METATILE_SIZE, METATILE_SIZE), (255, 0, 255))
    positions = [(0, 0), (8, 0), (0, 8), (8, 8)]
    for layer in (0, 1):
        for i in range(4):
            tile_id, xflip, yflip, pal = entries[layer * 4 + i]
            if tile_id < NUM_TILES_IN_PRIMARY:
                tiles_im, palettes = primary
            else:
                tiles_im, palettes = secondary
                tile_id -= NUM_TILES_IN_PRIMARY
            indices = get_tile_indices(tiles_im, tile_id)
            palette = palettes[pal]
            ox, oy = positions[i]
            if layer == 0:
                # Bottom layer always fully opaque (index 0 -> palette's own color 0)
                for y in range(TILE_SIZE):
                    for x in range(TILE_SIZE):
                        sx = TILE_SIZE - 1 - x if xflip else x
                        sy = TILE_SIZE - 1 - y if yflip else y
                        canvas.putpixel((ox + x, oy + y), palette[indices[sy][sx]])
            else:
                draw_tile(canvas, ox, oy, indices, palette, xflip, yflip)
    return canvas


def parse_entries(metatile_data, i):
    base = i * 16  # 8 entries * 2 bytes
    entries = []
    for j in range(8):
        raw = metatile_data[base + j * 2] | (metatile_data[base + j * 2 + 1] << 8)
        tile_id = raw & 0x3FF
        xflip = (raw >> 10) & 1
        yflip = (raw >> 11) & 1
        pal = (raw >> 12) & 0xF
        entries.append((tile_id, xflip, yflip, pal))
    return entries


def render_tileset_grid(name, id_offset, tiles_im, palettes, metatile_data, primary_pack, secondary_pack, out_path):
    num_metatiles = len(metatile_data) // 16
    rows = (num_metatiles + COLS - 1) // COLS
    cell = METATILE_SIZE * SCALE
    label_h = 10
    grid = Image.new("RGB", (COLS * cell, rows * (cell + label_h)), (32, 32, 32))
    draw = ImageDraw.Draw(grid)
    for i in range(num_metatiles):
        entries = parse_entries(metatile_data, i)
        mt_img = render_metatile(entries, primary_pack, secondary_pack)
        mt_img = mt_img.resize((cell, cell), Image.NEAREST)
        col, row = i % COLS, i // COLS
        x, y = col * cell, row * (cell + label_h)
        grid.paste(mt_img, (x, y))
        draw.text((x + 2, y + cell), str(i + id_offset), fill=(255, 255, 0))
    grid.save(out_path)
    print(f"wrote {out_path} ({num_metatiles} metatiles, ids {id_offset}-{id_offset + num_metatiles - 1})")


def render_map(map_bin_path, width, height, primary_name, secondary_name, out_path, scale=4):
    """Composite an entire map.bin into one image, exactly as it will look
    in-game (art only - no object events/NPCs/player, since those aren't
    part of the tile layout). Much faster than booting the emulator when
    the thing being checked is just 'does this layout look coherent.'"""
    primary_dir = os.path.join(REPO, "data/tilesets/primary", primary_name)
    secondary_dir = os.path.join(REPO, "data/tilesets/secondary", secondary_name)
    p_tiles, p_pals, p_meta, _ = load_tileset_dir(primary_dir)
    s_tiles, s_pals, s_meta, _ = load_tileset_dir(secondary_dir)
    combined_pals = p_pals[:NUM_PALS_IN_PRIMARY] + s_pals[NUM_PALS_IN_PRIMARY:]
    primary_pack = (p_tiles, combined_pals)
    secondary_pack = (s_tiles, combined_pals)

    with open(map_bin_path, "rb") as f:
        data = f.read()
    assert len(data) == width * height * 2, f"expected {width*height*2} bytes, got {len(data)}"

    cell = METATILE_SIZE * scale
    canvas = Image.new("RGB", (width * cell, height * cell), (255, 0, 255))
    cache = {}
    for i in range(width * height):
        raw = data[i * 2] | (data[i * 2 + 1] << 8)
        metatile_id = raw & 0x3FF
        if metatile_id not in cache:
            local_id = metatile_id - NUM_TILES_IN_PRIMARY
            entries = parse_entries(s_meta if local_id >= 0 else p_meta, local_id if local_id >= 0 else metatile_id)
            cache[metatile_id] = render_metatile(entries, primary_pack, secondary_pack).resize((cell, cell), Image.NEAREST)
        x, y = (i % width) * cell, (i // width) * cell
        canvas.paste(cache[metatile_id], (x, y))
    canvas.save(out_path)
    print(f"wrote {out_path} ({width}x{height} tiles)")


def main():
    if len(sys.argv) >= 2 and sys.argv[1] == "--map":
        # tileset_preview.py --map <map.bin> <width> <height> <primary> <secondary> <out.png>
        _, map_bin, width, height, primary_name, secondary_name, out_path = sys.argv[1:8]
        render_map(map_bin, int(width), int(height), primary_name, secondary_name, out_path)
        return

    if len(sys.argv) < 3:
        print(__doc__)
        sys.exit(1)
    primary_name, secondary_name = sys.argv[1], sys.argv[2]
    out_dir = sys.argv[3] if len(sys.argv) > 3 else "/tmp"
    os.makedirs(out_dir, exist_ok=True)

    primary_dir = os.path.join(REPO, "data/tilesets/primary", primary_name)
    secondary_dir = os.path.join(REPO, "data/tilesets/secondary", secondary_name)

    p_tiles, p_pals, p_meta, _ = load_tileset_dir(primary_dir)
    s_tiles, s_pals, s_meta, _ = load_tileset_dir(secondary_dir)

    # A metatile's palette index (0-15) always resolves against ONE combined
    # 16-slot table - palettes 0-5 from the primary tileset, 6-15 from the
    # secondary - regardless of which sheet (primary or secondary) the tile's
    # pixels come from. Using each tileset's own palette dir in isolation
    # would be wrong whenever a tile references a palette outside its own
    # tileset's real range (e.g. a secondary-sheet tile using a shared
    # primary palette like plain white/black).
    combined_pals = p_pals[:NUM_PALS_IN_PRIMARY] + s_pals[NUM_PALS_IN_PRIMARY:]
    primary_pack = (p_tiles, combined_pals)
    secondary_pack = (s_tiles, combined_pals)

    render_tileset_grid(primary_name, 0, p_tiles, p_pals, p_meta, primary_pack, secondary_pack,
                         os.path.join(out_dir, f"{primary_name}_metatiles.png"))
    render_tileset_grid(secondary_name, NUM_TILES_IN_PRIMARY, s_tiles, s_pals, s_meta, primary_pack, secondary_pack,
                         os.path.join(out_dir, f"{secondary_name}_metatiles.png"))


if __name__ == "__main__":
    main()
