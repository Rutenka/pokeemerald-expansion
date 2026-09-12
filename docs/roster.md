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
| Numel | Catchable | `Wasteland_MillersCut`, wild encounter (levels 8-12) | Bulky fire/ground, slow physical tank | Species choice reused from Jagged Pass's real vanilla table; levels rebalanced down (vanilla uses 20-22, far too strong this early) |
| Machop | Catchable | `Wasteland_MillersCut`, wild encounter (levels 8-12) | Early physical fighter | Same source/rebalancing as Numel above |
| Koffing | Catchable | `Wasteland_MillersCut`, wild encounter (levels 8-12); also on the Ashband Enforcer's team | Toxic-gas support/attrition | First roster addition not sourced from the reused vanilla table - picked for the toxic/bunker checkpoint theme, per selection principle 2 |
| Mightyena | Catchable (evolution only, not yet in any wild table) | Evolves from Poochyena at level 18 (plain vanilla level-up); also the Ashband Enforcer's lead | Physical raider "attack dog" | Ties the Ashband's dog motif together across the Scout (Poochyena) and Enforcer (Mightyena) - no new work needed, this is Poochyena's real vanilla evolution |
| Zigzagoon (Ashband Lookout's team) | see above | Trainer-only for now, level 9 | — | Same species already on the roster, just also used as a trainer's Pokémon for variety instead of another Poochyena |

**Trainer roster so far** (all `TRAINER_CLASS_ASHBAND`, reusing the vanilla Aqua Grunt
battle sprite purely as art - see the Twentieth feature entry in CLAUDE.md): Scout
(`Wasteland_Road`, Poochyena Lv7), Lookout (`Wasteland_MillersCut`, Zigzagoon Lv9),
Checkpoint Grunt (`Wasteland_AshbandCheckpoint`, Poochyena Lv11), Enforcer
(`Wasteland_AshbandCheckpoint` boss, Mightyena Lv14 + Koffing Lv13). Only 9 total
custom trainer slots exist before trainer-flag space overflows (see
`include/constants/opponents.h`) - 4 used, 5 remain.

**Open**: no gym-leader/proper "regional boss" (as opposed to a checkpoint-tier
enforcer) exists yet. Brightwell's own non-service buildings and Grayford are still
unconnected/undeveloped.
