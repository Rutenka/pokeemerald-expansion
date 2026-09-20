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
| Magnemite | Catchable (trainer-only for now) | `Wasteland_RustboroGym`, Corporate trainer's team (Lv14) | Fast special/status disruptor, immune to Ground | First "clean/corporate/industrial" pick - contrasts the scrappy wasteland fauna so far, fits the security-drone framing of the assessment center |
| Baltoy | Catchable (trainer-only for now) | `Wasteland_RustboroGym`, Corporate trainer's team (Lv14) | Bulky psychic/ground utility, Rapid Spin support | Ancient-tech/ground-psychic fit for the corporate faction; ties into the setting's "Pokémon-derived psychic network" theme |
| Voltorb | Catchable (trainer-only for now) | `Wasteland_RustboroGym`, Corporate trainer's team (Lv15) | Fast special disruptor | Round drone/security-orb read, matches the surveillance theme |
| Magneton | Catchable (evolution only, not yet in any wild table) | Evolves from Magnemite (plain vanilla level-up); also the Overseer boss's lead | Bulkier special/status disruptor, Steel/Electric coverage | Boss-tier step up from the gauntlet trainer's Magnemite |
| Solrock | Catchable (trainer-only for now) | `Wasteland_RustboroGym` boss, Overseer's team (Lv18) | Bulky psychic/rock, sets up with Cosmic Power | Direct thematic tie to the setting's psychic-control-network premise - a "surveillance eye" read |
| Porygon | Catchable (trainer-only for now) | `Wasteland_RustboroGym` boss, Overseer's ace (Lv19) | Recovery + Agility stall/sweeper, all-type coverage via Conversion | Literally an artificial/digital Pokémon - the single best-fitting species in the whole roster for "a corporation that builds Pokémon-derived control tech," used deliberately as the boss's ace |
| Elgyem | Catchable | `Wasteland_Rustboro`, wild encounter via a single scripted `wildbattle` (Lv13, Selin's pet, part of the pre-Gym incident quest) - guaranteed to end up on the player's team one way or another (catch it in the fight, or Selin gives it to you afterward if you don't) | Early pure Psychic utility, sets up for Beheeyem later | First living (not artificial) "network-affected" Pokémon - deliberately contrasts the Gym's mechanical Magnemite/Baltoy/Voltorb with something the network can hurt too, not just power; its own real Pokédex lore (telepathy from radio-wave/antenna exposure) is a near-literal match for the control-network premise, picked 2026-09-15 to replace an earlier Natu placeholder for exactly that reason |
| Absol | Catchable (trade only) | `Wasteland_Rustboro_Trader`, in-game trade (`INGAME_TRADE_WASTELAND_ABSOL`, src/data/trade.h) for a Poochyena | Fast physical sweeper, Dark-type glass cannon | Picked by Viktor 2026-09-15 for its real Pokédex premise (senses disaster, tries to warn people, gets blamed for causing it instead) - a direct mirror of this story's own premise (Pokémon panicking when the network failed, then blamed for a collapse humans caused). Distinct battle role from the existing Dark-types (Houndoom's a special sweeper, Mightyena's a balanced physical attacker), so kept despite the shared typing per the "distinct roles over headcount" principle |
| Taillow | Catchable | `Wasteland_EastRoad`, wild encounter (levels 14-19) | Early fast physical Flying attacker | Territory 3's connecting route - a genuinely new roster addition, picked for a fast physical role nothing else on the roster yet fills. Originally added on `Wasteland_SouthRoad` (2026-09-15/16), which was retired the next day - see the Thirty-sixth feature entry - and rebuilt as `Wasteland_EastRoad` instead; this row now reflects the current map |
| Miltank | Catchable (trainer-only for now) | `Wasteland_Haverbrook_ProvingGrounds`, Garrick's team (Lv18) | Bulky Normal-type support/attacker | First pick for territory 3's "sturdy, reliable working-partner Pokemon" theme (Thirty-first feature entry) - a real farm/community-provider Pokemon, not a weapon |
| Mudbray | Catchable (trainer-only for now) | `Wasteland_Haverbrook_ProvingGrounds`, Garrick's ace (Lv20) | Physical Ground-type workhorse, Strength/Bulldoze/Iron Defense | Its own real Pokedex identity is literally a plow/draft-animal Pokemon - the single best-fitting species for the "sturdy workhorse" territory-3 theme, deliberately left unevolved (Mudsdale needs Lv30) to match this story point's level range |
| Abra | Catchable | `Wasteland_EastRoad`, wild encounter (levels 14-16) | Early Psychic special sweeper (evolves into Kadabra/Alakazam later) | Added 2026-09-16 when South Road was rebuilt as East Road (reused Route116's real vanilla table, which already included it) - fills a distinct special-sweeper role nothing else on the roster covers yet |

**Trainer roster so far**: the Ashband (all `TRAINER_CLASS_ASHBAND`, reusing the
vanilla Aqua Grunt battle sprite purely as art - see the Twentieth feature entry in
CLAUDE.md): Scout (`Wasteland_Road`, Poochyena Lv7), Lookout (`Wasteland_MillersCut`,
Zigzagoon Lv9), Checkpoint Grunt (`Wasteland_AshbandCheckpoint`, Poochyena Lv11),
Enforcer (`Wasteland_AshbandCheckpoint` boss, Mightyena Lv14 + Koffing Lv13). The
corporate settlement (all `TRAINER_CLASS_CORPORATE`, reusing "Expert M/F" and "Leader
Roxanne" battle sprites as art - see the Twenty-third feature entry): Kessler
(`Wasteland_RustboroGym`, Magnemite Lv14), Priya (`Wasteland_RustboroGym`, Baltoy
Lv14), Drummond (`Wasteland_RustboroGym`, Voltorb Lv15), Overseer Reyes
(`Wasteland_RustboroGym` boss, Magneton Lv17 + Solrock Lv18 + Porygon Lv19 - the
game's first proper multi-mon boss fight). Territory 3's own boss (`TRAINER_CLASS_PKMN_
RANGER`, reusing the real "Pokemon Ranger M" battle pic - not corporate, not raider,
a settlement protector): Garrick (`Wasteland_Haverbrook_ProvingGrounds`, Miltank Lv18
+ Mudbray Lv20). **This is now genuinely the 9th and last of the 9 total custom
trainer slots** (this doc previously said all 9 were already spent before Garrick was
added - that was a real counting error, corrected 2026-09-15; only 8 were actually
used at the time). **Update 2026-09-20: the limit is lifted** - ids 864-927 (64 more
custom trainers) now work via `TRAINER_FLAG_ID()` in `include/constants/flags.h`, which
keeps the save layout unchanged. Add new trainers starting at id 864; see
`test/wasteland_trainer_flags.c` for the guard tests.

**Open**: Brightwell's own non-service buildings and Grayford are still
unconnected/undeveloped. Devon Corp specifically is still deliberately left closed (a
real future story beat, not just an unbuilt building - see the Twenty-seventh feature
entry) - the rest of Rustboro's real buildings (2 flats, the Cutter's house, the
trader's house, 2 plain houses, the Pokémon School) were opened 2026-09-15, see the
Thirty-eighth feature entry in CLAUDE.md.

**The pre-Gym "incident" side quest** (see CLAUDE.md's Thirty-third feature entry, and
the "real happening" rebuild in the entry after it, 2026-09-15) uses `wildbattle`/
`givemon` instead of new Trainers specifically because all 9 custom trainer slots are
already spent (above) - Voltorb and Baltoy reuse the exact species already fighting for
the Gym itself (a deliberate small "preview of what's coming"), Elgyem is the one new
addition, picked to be the quest's single catchable reward. As of 2026-09-15, Selin's
Voltorb and Baltoy are Lv16 (up from Lv13) and both hold `ITEM_EVIOLITE` - a real
tactical step up per Viktor's request, since both are unevolved species and the +50%
Def/SpDef genuinely toughens them against an early Houndour. Elgyem stays at Lv13/no
item, since it's the catchable reward rather than part of the difficulty ask.
