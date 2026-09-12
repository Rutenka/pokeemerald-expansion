# Pokémon Wasteland — regional roster tracker

Tracks two separate things per species, on purpose (see CLAUDE.md's design brief):
**supported** (exists in `species_info`, so it's implementable) is not the same as
**catchable** (actually reachable by the player via wild encounter, gift, or trade).
Built chapter-by-chapter, not all at once — only fill in a species once it's actually
touched by real content.

Selection principles (from CLAUDE.md, keep every entry checked against these):
multi-gen, thematic fit (survival/scrappy/industrial/feral/toxic/urban-decay), mostly
complete evolution lines, distinct battle roles over headcount, no near-duplicate
niches, legendaries as rare story beats only, nothing gimmick-dependent (Mega/Gmax/
Tera are disabled project-wide), progressive reveal tied to exploration.

| Species | Status | Catchable where | Battle role | Notes |
|---|---|---|---|---|
| Houndour (Alder) | Supported | Gift — Safe Room, from Dad, opening scene | Early fast special attacker, fire/dark utility | Custom: BST 360 (vs 330), ability locked to Flash Fire, not breedable (No Eggs Discovered group), evolves at level 32 instead of 24 |
| Houndoom (Alder) | Supported | Evolves from Houndour (Alder) at level 32, plain level-up, no extra gate | Bulky-ish special sweeper, fire/dark | BST 575 (vs 500), same ability/breeding restrictions as its pre-evolution |
| Poochyena | Catchable | `Wasteland_Road`, wild encounter (levels 2-5) | Early physical/fast disruptor | Reused Route101's real vanilla encounter table as-is |
| Zigzagoon | Catchable | `Wasteland_Road`, wild encounter (levels 2-5) | Early utility/Pickup | Reused Route101's real vanilla encounter table as-is |
| Wurmple | Catchable | `Wasteland_Road`, wild encounter (levels 2-5) | Early-game filler, splits into two lines | Reused Route101's real vanilla encounter table as-is |

**Open**: no gym-leader/warlord-boss trainer roster exists yet (no trainer battle of
any kind exists in this chapter yet). Nothing has been decided for Brightwell,
Grayford, or any settlement beyond the starter and the Route101 filler table above.
