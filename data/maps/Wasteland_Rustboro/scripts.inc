@ Reuses the real, whole vanilla RustboroCity layout verbatim (per the
@ standing "no crop-and-stitch, reskin only" rule) - Devon Corporation's real
@ home city in vanilla, which is exactly the fit for a corporate-controlled
@ settlement. All 16 real NPC positions/sprites kept as-is; only their
@ dialogue is reflavored. Most of the real building doors are deliberately
@ left unwired for now (same accepted trade-off as Brightwell's own unbuilt
@ houses) - only the Gym (the boss), Mart, and Pokemon Center are built.
@ Devon Corp's own doors are left unwired on purpose, with a sign explaining
@ why (restricted access), rather than silently doing nothing.
Wasteland_Rustboro_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Wasteland_Rustboro_OnTransition
	.byte 0

Wasteland_Rustboro_OnTransition:
	setrespawn HEAL_LOCATION_WASTELAND_RUSTBORO
	@ Idempotent - keeps Reyes's outdoor cutscene object permanently hidden
	@ from the passive per-map spawn check on every load; she only ever
	@ appears via the explicit `addobject` in her cutscene below.
	setflag FLAG_WASTELAND_REYES_HIDDEN
	end

@ The actual return path to Miller's Cut - real bug found and fixed
@ 2026-09-14: the plain warp_events entry here (shared with the arrival
@ landing coordinate) never fires on its own, because this tile has no real
@ door/warp *behavior* tag (checklist item 16's exact lesson) - a
@ warp_events array entry is only ever real destination *data* that
@ something else (a door tile's TryDoorWarp check, or an explicit `warp`
@ script command) has to actually invoke; simply listing a coordinate there
@ does nothing on its own. Confirmed via a live headless test: walking onto
@ (15,59) did nothing at all, on a build that had already shipped the sign
@ pointing right at it. Fixed with the same coord_event + `warp` command
@ pattern this project used before real doors became the default (see the
@ Eighth feature entry) - safe to reuse the landing tile itself for the
@ trigger here (not the usual "landing != trigger" rule) specifically
@ because a coord_event never fires on the frame of a warp *arrival* (no
@ real step taken), only on a later, genuine step onto that same tile - so
@ arriving players are never bounced immediately, only players who
@ deliberately walk back into this corner to leave.
Wasteland_Rustboro_EventScript_ExitToCheckpoint::
	warp MAP_WASTELAND_CORP_CHECKPOINT, 1
	waitstate
	end

Wasteland_Rustboro_EventScript_Arrival::
	lockall
	msgbox Wasteland_Rustboro_Text_Arrival1, MSGBOX_DEFAULT
	closemessage
	msgbox Wasteland_Rustboro_Text_Arrival2, MSGBOX_DEFAULT
	closemessage
	msgbox Wasteland_Rustboro_Text_Arrival3, MSGBOX_DEFAULT
	closemessage
	msgbox Wasteland_Rustboro_Text_Arrival4, MSGBOX_DEFAULT
	closemessage
	msgbox Wasteland_Rustboro_Text_Arrival5, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_SEEN_RUSTBORO_ARRIVAL
	releaseall
	end

Wasteland_Rustboro_Text_Arrival1::
	.string "Past the checkpoint, the road turns\n"
	.string "to real pavement.\p"
	.string "Streetlights. Clean walls. A city\l"
	.string "that still works.$"

Wasteland_Rustboro_Text_Arrival2::
	.string "Nobody here looks like they've seen\n"
	.string "what's out on the road.\p"
	.string "Maybe that's the point.$"

@ Direct, per Viktor's confirmed call (2026-09-14): the player has real,
@ written proof (the checkpoint records room's ledger) that Devon
@ Corporation supplies the Ashband. Arriving here is not incidental - it's
@ the reason this city matters right now.
Wasteland_Rustboro_Text_Arrival3::
	.string "That ledger's still fresh in your\n"
	.string "head. DEVON CORPORATION - LOGISTICS.\p"
	.string "This is their city. If anyone knows\n"
	.string "why they're arming the people who\l"
	.string "took DAD, it's someone in here.$"

@ Rewritten 2026-09-15 (v2, same day) per Viktor's ask for an unmissable,
@ up-front explanation of why the Gym even matters, delivered by an actual
@ person rather than disembodied narration - "someone who explains how the
@ town works." Still the same coord_event-triggered arrival narration (no
@ new object budget spent, and guaranteed to fire once, unlike a walk-up
@ NPC the player could simply avoid), just voiced as a specific local
@ stopping the player rather than third-person text.
Wasteland_Rustboro_Text_Arrival4::
	.string "“You're not from here,” a woman\n"
	.string "minding a supply cart says, not\l"
	.string "really asking.\p"
	.string "“This city runs because the\n"
	.string "Overseer's people say it runs.”$"

Wasteland_Rustboro_Text_Arrival5::
	.string "“You want to go anywhere that\n"
	.string "matters in this city, you clear\l"
	.string "Assessment first. That's not a\l"
	.string "suggestion.”\p"
	.string "She's already looking past you\n"
	.string "before you can ask anything else.$"

Wasteland_Rustboro_EventScript_Woman::
	lock
	faceplayer
	msgbox Wasteland_Rustboro_Text_Woman, MSGBOX_DEFAULT
	release
	end

@ Rebuilt 2026-09-15 per Viktor's ask for a real "happening" - a single
@ dramatic incident with weight, not an item-fetch quest. FatMan is now pure
@ flavor (no mechanic tied to him); the Gym guard is the front door that
@ sends the player looking for the trouble (see GymGuard below); Man2 and
@ the Scientist point toward it without fighting it themselves; Selin's
@ location is where it's all converging, and talking to her runs all 3
@ `wildbattle` encounters back to back; beating the last one brings Reyes
@ herself out to grant clearance directly. No new Trainer, no new map - see
@ docs/roster.md, the custom Trainer ID budget is fully spent.
Wasteland_Rustboro_EventScript_FatMan::
	lock
	faceplayer
	msgbox Wasteland_Rustboro_Text_FatMan, MSGBOX_DEFAULT
	release
	end

Wasteland_Rustboro_EventScript_NinjaBoy::
	lock
	faceplayer
	msgbox Wasteland_Rustboro_Text_NinjaBoy, MSGBOX_DEFAULT
	release
	end

Wasteland_Rustboro_EventScript_Boy2::
	lock
	faceplayer
	msgbox Wasteland_Rustboro_Text_Boy2, MSGBOX_DEFAULT
	release
	end

Wasteland_Rustboro_EventScript_Man1::
	lock
	faceplayer
	msgbox Wasteland_Rustboro_Text_Man1, MSGBOX_DEFAULT
	release
	end

@ Relocated 2026-09-15 (v3, same day) to stand with the rest of the crowd
@ per Viktor's ask for it to really read as "what is going on here???" -
@ a bigger cluster than just Selin/Man2/Scientist. Woven into the group
@ cutscene too, see Wasteland_Rustboro_Text_LittleBoyReaction below.
Wasteland_Rustboro_EventScript_LittleBoy::
	lock
	faceplayer
	goto_if_unset FLAG_WASTELAND_RUSTBORO_INCIDENT_STARTED, Wasteland_Rustboro_EventScript_LittleBoyNormal
	goto_if_set FLAG_WASTELAND_RUSTBORO_PET_RESOLVED, Wasteland_Rustboro_EventScript_LittleBoyAfter
	msgbox Wasteland_Rustboro_Text_LittleBoyReaction, MSGBOX_DEFAULT
	release
	end

Wasteland_Rustboro_EventScript_LittleBoyNormal::
	msgbox Wasteland_Rustboro_Text_LittleBoy, MSGBOX_DEFAULT
	release
	end

Wasteland_Rustboro_EventScript_LittleBoyAfter::
	msgbox Wasteland_Rustboro_Text_LittleBoyAfter, MSGBOX_DEFAULT
	release
	end

Wasteland_Rustboro_EventScript_LittleGirl::
	lock
	faceplayer
	goto_if_unset FLAG_WASTELAND_RUSTBORO_INCIDENT_STARTED, Wasteland_Rustboro_EventScript_LittleGirlNormal
	goto_if_set FLAG_WASTELAND_RUSTBORO_PET_RESOLVED, Wasteland_Rustboro_EventScript_LittleGirlAfter
	msgbox Wasteland_Rustboro_Text_LittleGirlReaction, MSGBOX_DEFAULT
	release
	end

Wasteland_Rustboro_EventScript_LittleGirlNormal::
	msgbox Wasteland_Rustboro_Text_LittleGirl, MSGBOX_DEFAULT
	release
	end

Wasteland_Rustboro_EventScript_LittleGirlAfter::
	msgbox Wasteland_Rustboro_Text_LittleGirlAfter, MSGBOX_DEFAULT
	release
	end

Wasteland_Rustboro_EventScript_DevonEmployee1::
	lock
	faceplayer
	msgbox Wasteland_Rustboro_Text_DevonEmployee1, MSGBOX_DEFAULT
	release
	end

@ Referenced by Viktor's confirmed decision (2026-09-14): the Overseer's
@ Assessment Center is a real gate now, not a skippable side fight - this is
@ the guard telling the player that directly, before and after they clear it.
@ Devon Corp's own door stays unwired (no interior built yet - see the
@ standing "closed for now" note above), but the dialogue already sets up
@ why it matters once that interior exists.
Wasteland_Rustboro_EventScript_CorpGuard::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_CORP_OVERSEER, Wasteland_Rustboro_EventScript_CorpGuardCleared
	msgbox Wasteland_Rustboro_Text_CorpGuard, MSGBOX_DEFAULT
	release
	end

Wasteland_Rustboro_EventScript_CorpGuardCleared::
	msgbox Wasteland_Rustboro_Text_CorpGuardCleared, MSGBOX_DEFAULT
	release
	end

@ Simplified 2026-09-15 - no longer part of the sponsorship mechanic (Reyes
@ grants that directly now, see Selin's script below). Pure flavor.
Wasteland_Rustboro_EventScript_DevonEmployee2::
	lock
	faceplayer
	msgbox Wasteland_Rustboro_Text_DevonEmployee2, MSGBOX_DEFAULT
	release
	end

@ Rewritten 2026-09-15 (v2, same day) - relocated to stand next to Selin as
@ part of the crowd Viktor asked for, rather than a separate NPC pointing
@ the player elsewhere. Man2's own original line ("You get used to the
@ drones... they're not even armed. Probably.") is what foreshadowed this
@ drone in the first place, and his relocated position is also what makes
@ his reaction line during the fight land.
Wasteland_Rustboro_EventScript_Man2::
	lock
	faceplayer
	goto_if_unset FLAG_WASTELAND_RUSTBORO_INCIDENT_STARTED, Wasteland_Rustboro_EventScript_Man2Normal
	goto_if_set FLAG_WASTELAND_RUSTBORO_PET_RESOLVED, Wasteland_Rustboro_EventScript_Man2After
	msgbox Wasteland_Rustboro_Text_Man2Reaction, MSGBOX_DEFAULT
	release
	end

Wasteland_Rustboro_EventScript_Man2Normal::
	msgbox Wasteland_Rustboro_Text_Man2, MSGBOX_DEFAULT
	release
	end

Wasteland_Rustboro_EventScript_Man2After::
	msgbox Wasteland_Rustboro_Text_Man2After, MSGBOX_DEFAULT
	release
	end

@ Rewritten 2026-09-15 (v2, same day) - same treatment as Man2 above. The
@ Scientist's own original line ("Please don't touch the equipment. It
@ remembers.") is what foreshadowed this.
Wasteland_Rustboro_EventScript_Scientist::
	lock
	faceplayer
	goto_if_unset FLAG_WASTELAND_RUSTBORO_INCIDENT_STARTED, Wasteland_Rustboro_EventScript_ScientistNormal
	goto_if_set FLAG_WASTELAND_RUSTBORO_PET_RESOLVED, Wasteland_Rustboro_EventScript_ScientistAfter
	msgbox Wasteland_Rustboro_Text_ScientistReaction, MSGBOX_DEFAULT
	release
	end

Wasteland_Rustboro_EventScript_ScientistNormal::
	msgbox Wasteland_Rustboro_Text_Scientist, MSGBOX_DEFAULT
	release
	end

Wasteland_Rustboro_EventScript_ScientistAfter::
	msgbox Wasteland_Rustboro_Text_ScientistAfter, MSGBOX_DEFAULT
	release
	end

Wasteland_Rustboro_EventScript_Boy1::
	lock
	faceplayer
	msgbox Wasteland_Rustboro_Text_Boy1, MSGBOX_DEFAULT
	release
	end

Wasteland_Rustboro_EventScript_GymSign::
	msgbox Wasteland_Rustboro_Text_GymSign, MSGBOX_SIGN
	end

Wasteland_Rustboro_EventScript_SchoolSign::
	msgbox Wasteland_Rustboro_Text_SchoolSign, MSGBOX_SIGN
	end

Wasteland_Rustboro_EventScript_CitySign::
	msgbox Wasteland_Rustboro_Text_CitySign, MSGBOX_SIGN
	end

Wasteland_Rustboro_EventScript_DevonCorpSign::
	msgbox Wasteland_Rustboro_Text_DevonCorpSign, MSGBOX_SIGN
	end

Wasteland_Rustboro_EventScript_PassSign::
	msgbox Wasteland_Rustboro_Text_PassSign, MSGBOX_SIGN
	end

Wasteland_Rustboro_EventScript_PrivateResidenceSign::
	msgbox Wasteland_Rustboro_Text_PrivateResidenceSign, MSGBOX_SIGN
	end

Wasteland_Rustboro_Text_Woman::
	.string "The ration line moves faster if you\n"
	.string "don't ask questions at the window.\p"
	.string "I learned that the slow way.$"

Wasteland_Rustboro_Text_FatMan::
	.string "Thirty years I've filed compliance\n"
	.string "reports for this district.\p"
	.string "Not one has ever been read, as far\l"
	.string "as I can tell. I file them anyway.\p"
	.string "And no, before you ask - I can't\n"
	.string "help you with anything. Take it up\l"
	.string "with Coordination.$"

Wasteland_Rustboro_Text_NinjaBoy::
	.string "They test us for “aptitude” now.\n"
	.string "I scored high in obedience.\p"
	.string "I'm still not sure that's supposed\l"
	.string "to be a compliment.$"

Wasteland_Rustboro_Text_Boy2::
	.string "Dad says it's worse out past the\n"
	.string "checkpoint.\p"
	.string "I wouldn't know. I've never been\l"
	.string "past the checkpoint.$"

Wasteland_Rustboro_Text_Man1::
	.string "The streetlights never really turn\n"
	.string "off here. You get used to it.\p"
	.string "Or you stop sleeping. Either way,\l"
	.string "you get used to it.$"

Wasteland_Rustboro_Text_LittleBoy::
	.string "We're not allowed near the tower\n"
	.string "after dark.\p"
	.string "Nobody ever said why. Nobody has\l"
	.string "had to.$"

Wasteland_Rustboro_Text_LittleGirl::
	.string "I asked my teacher what the company\n"
	.string "actually does.\p"
	.string "She said “everything,” and smiled\l"
	.string "for exactly the right amount of\l"
	.string "time.$"

Wasteland_Rustboro_Text_LittleBoyReaction::
	.string "What is even GOING ON?! First the\n"
	.string "drone, then the display, now this?!\p"
	.string "I'm not scared. I'm just… taking\n"
	.string "notes. For later.$"

Wasteland_Rustboro_Text_LittleBoyAfter::
	.string "Best day ever. Don't tell my mom I\n"
	.string "said that.$"

Wasteland_Rustboro_Text_LittleGirlReaction::
	.string "Is this normal?! Nobody said this\n"
	.string "was normal!$"

Wasteland_Rustboro_Text_LittleGirlAfter::
	.string "My teacher's going to have SO many\n"
	.string "questions tomorrow.$"

Wasteland_Rustboro_Text_DevonEmployee1::
	.string "Badge in, badge out. If your badge\n"
	.string "doesn't scan, you were never here\l"
	.string "today.\p"
	.string "That's not a threat. That's just\l"
	.string "how the door works.$"

Wasteland_Rustboro_Text_CorpGuard::
	.string "This area is monitored for your\n"
	.string "safety and ours.\p"
	.string "Mostly ours.\p"
	.string "Nobody gets past this door without\n"
	.string "Assessment clearance. That's not me\l"
	.string "being difficult - I just don't have\l"
	.string "the authority to let you through.$"

Wasteland_Rustboro_Text_CorpGuardCleared::
	.string "Cleared Assessment, huh.\p"
	.string "That's a start. It's not the same\n"
	.string "as clearance for this building - but\l"
	.string "it's the only door in this city that\l"
	.string "ever opens for anyone.$"

Wasteland_Rustboro_Text_DevonEmployee2::
	.string "We don't call it a control network\n"
	.string "anymore. Corporate rebrand.\p"
	.string "“Coordination framework.” Feels\l"
	.string "completely different, I'm sure.$"

Wasteland_Rustboro_Text_Man2::
	.string "You get used to the drones after a\n"
	.string "while.\p"
	.string "They're not even armed. Probably.$"

Wasteland_Rustboro_Text_Man2Reaction::
	.string "That's MY drone! Well - not mine,\n"
	.string "but I'm the one who reports it\l"
	.string "missing every week.\p"
	.string "Never thought I'd see it do THAT.$"

Wasteland_Rustboro_Text_Man2After::
	.string "Still can't believe it. Six years\n"
	.string "on this block, never seen one go\l"
	.string "like that before today.$"

Wasteland_Rustboro_Text_Scientist::
	.string "Please don't touch the equipment.\n"
	.string "It remembers.$"

Wasteland_Rustboro_Text_ScientistReaction::
	.string "I told them not to put unsupervised\n"
	.string "hardware in a public display case!\p"
	.string "Nobody ever listens to the guy\n"
	.string "who's right.$"

Wasteland_Rustboro_Text_ScientistAfter::
	.string "Back in its case. Bolted down,\n"
	.string "this time.\p"
	.string "That's the whole fix, apparently.$"

Wasteland_Rustboro_Text_Boy1::
	.string "It's not really a gym. It's an\n"
	.string "assessment center.\p"
	.string "“Gym” just polls better with the\l"
	.string "public.$"

Wasteland_Rustboro_Text_GymSign::
	.string "OVERSEER'S ASSESSMENT CENTER\n"
	.string "Field Aptitude Certification\l"
	.string "(formerly: “Gym”)$"

Wasteland_Rustboro_Text_SchoolSign::
	.string "CORPORATE POKéMON APTITUDE SCHOOL\n"
	.string "Compliance is Confidence$"

Wasteland_Rustboro_Text_CitySign::
	.string "RUSTBORO\n"
	.string "A Model Community.\l"
	.string "(Please remain calm.)$"

Wasteland_Rustboro_Text_DevonCorpSign::
	.string "DEVON CORPORATION\n"
	.string "Regional Headquarters\l"
	.string "RESTRICTED ACCESS - PERSONNEL ONLY$"

Wasteland_Rustboro_Text_PassSign::
	.string "MILLER'S CUT PASS\n"
	.string "Checkpoint clearance required\l"
	.string "beyond this point.$"

Wasteland_Rustboro_Text_PrivateResidenceSign::
	.string "PRIVATE RESIDENCE$"

@ The return path to the checkpoint/Miller's Cut sits on plain, unmarked
@ ground here (checklist item 16's exact failure class - a real, working
@ warp a player has no way to distinguish from ordinary pavement) - Viktor
@ hit this directly (2026-09-14), reporting no way back to "the second
@ road" at all. Fixed with a sign, same low-risk pattern as the corporate
@ gate fix rather than touching the tile itself.
Wasteland_Rustboro_EventScript_CheckpointRoadSign::
	msgbox Wasteland_Rustboro_Text_CheckpointRoadSign, MSGBOX_SIGN
	end

Wasteland_Rustboro_Text_CheckpointRoadSign::
	.string "CHECKPOINT ROAD\n"
	.string "South, past the marker stones -\l"
	.string "the way back to Miller's Cut.$"

@ Rebuilt 2026-09-15 into the actual front door of the incident, replacing
@ the old sponsorship-fetch mechanic. First talk sends the player looking
@ for the trouble in the city (see Selin's script below); the guard's own
@ object_event "flag" field still hides him automatically once
@ FLAG_HAS_GYM_SPONSORSHIP is set (now granted by Reyes directly), same
@ proven mechanism as the Miller's Cut blockade.
Wasteland_Rustboro_EventScript_GymGuard::
	lock
	faceplayer
	goto_if_set FLAG_WASTELAND_RUSTBORO_INCIDENT_STARTED, Wasteland_Rustboro_EventScript_GymGuardStillWaiting
	msgbox Wasteland_Rustboro_Text_GymGuardFirst, MSGBOX_DEFAULT
	setflag FLAG_WASTELAND_RUSTBORO_INCIDENT_STARTED
	release
	end

Wasteland_Rustboro_EventScript_GymGuardStillWaiting::
	msgbox Wasteland_Rustboro_Text_GymGuardStillWaiting, MSGBOX_DEFAULT
	release
	end

Wasteland_Rustboro_Text_GymGuardFirst::
	.string "Nobody challenges Assessment\n"
	.string "without clearance. That's not new.\p"
	.string "What IS new is half the city\n"
	.string "calling in about Pokémon acting\l"
	.string "wrong.\p"
	.string "Sort that out, and maybe someone\n"
	.string "with real standing will vouch for\l"
	.string "you.$"

Wasteland_Rustboro_Text_GymGuardStillWaiting::
	.string "Still no clearance.\p"
	.string "Whatever's going on out there, it\n"
	.string "isn't finished yet.$"

@ Rebuilt 2026-09-15 - the incident's finale. Talking to Selin once the
@ guard has sent the player looking runs all 3 `wildbattle` encounters back
@ to back (Voltorb, then Baltoy, then Elgyem), skipping any already won so a
@ loss mid-sequence can be resumed by talking to her again rather than
@ losing progress. Beating the last one brings Reyes herself out for a
@ short cutscene that grants FLAG_HAS_GYM_SPONSORSHIP directly - see
@ Wasteland_Rustboro_EventScript_SelinReyesArrives below.
@ Voltorb/Baltoy raised to level 16 with Eviolite (2026-09-15, per Viktor's
@ ask for a real tactical step up from the starter Houndour) - both are
@ unevolved species, so Eviolite's +50% Def/SpDef genuinely toughens them
@ up rather than just padding a stat total. Elgyem stays at its original
@ level/no item - it's the catchable reward, not part of the difficulty ask.
Wasteland_Rustboro_EventScript_Selin::
	lock
	faceplayer
	goto_if_set FLAG_HAS_GYM_SPONSORSHIP, Wasteland_Rustboro_EventScript_SelinAfter
	goto_if_unset FLAG_WASTELAND_RUSTBORO_INCIDENT_STARTED, Wasteland_Rustboro_EventScript_SelinNormal
	goto_if_set FLAG_WASTELAND_RUSTBORO_DRONE_RESOLVED, Wasteland_Rustboro_EventScript_SelinCheckArtifact
	@ Rewritten 2026-09-15 (v3, same day) into a real multi-voice cutscene
	@ per Viktor's ask - `lockall` freezes Man2, the Scientist, LittleBoy
	@ and LittleGirl too (all four relocated to stand right here, see the
	@ map.json notes above their own scripts) so their reaction lines read
	@ as part of one frozen scene, not separate conversations. LittleBoy's
	@ line added this round specifically to sell the "what is even going
	@ on?!" chaos Viktor asked for with a bigger-feeling crowd.
	lockall
	msgbox Wasteland_Rustboro_Text_SelinConverge1, MSGBOX_DEFAULT
	msgbox Wasteland_Rustboro_Text_Man2Reaction, MSGBOX_DEFAULT
	msgbox Wasteland_Rustboro_Text_ScientistReaction, MSGBOX_DEFAULT
	msgbox Wasteland_Rustboro_Text_LittleBoyReaction, MSGBOX_DEFAULT
	msgbox Wasteland_Rustboro_Text_SelinConverge2, MSGBOX_DEFAULT
Wasteland_Rustboro_EventScript_SelinDroneBattle::
	setwildbattle SPECIES_VOLTORB, 16, ITEM_EVIOLITE
	waitse
	playmoncry SPECIES_VOLTORB, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, Wasteland_Rustboro_EventScript_SelinDroneWon
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Wasteland_Rustboro_EventScript_SelinDroneWon
	releaseall
	end

Wasteland_Rustboro_EventScript_SelinDroneWon::
	setflag FLAG_WASTELAND_RUSTBORO_DRONE_RESOLVED
	msgbox Wasteland_Rustboro_Text_SelinOneDown, MSGBOX_DEFAULT
Wasteland_Rustboro_EventScript_SelinCheckArtifact::
	goto_if_set FLAG_WASTELAND_RUSTBORO_ARTIFACT_RESOLVED, Wasteland_Rustboro_EventScript_SelinCheckPet
Wasteland_Rustboro_EventScript_SelinArtifactBattle::
	setwildbattle SPECIES_BALTOY, 16, ITEM_EVIOLITE
	waitse
	playmoncry SPECIES_BALTOY, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, Wasteland_Rustboro_EventScript_SelinArtifactWon
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Wasteland_Rustboro_EventScript_SelinArtifactWon
	releaseall
	end

Wasteland_Rustboro_EventScript_SelinArtifactWon::
	setflag FLAG_WASTELAND_RUSTBORO_ARTIFACT_RESOLVED
	msgbox Wasteland_Rustboro_Text_SelinTwoDown, MSGBOX_DEFAULT
Wasteland_Rustboro_EventScript_SelinCheckPet::
	goto_if_set FLAG_WASTELAND_RUSTBORO_PET_RESOLVED, Wasteland_Rustboro_EventScript_SelinReyesArrives
Wasteland_Rustboro_EventScript_SelinPetBattle::
	msgbox Wasteland_Rustboro_Text_SelinAlert, MSGBOX_DEFAULT
	setwildbattle SPECIES_ELGYEM, 13, ITEM_NONE
	waitse
	playmoncry SPECIES_ELGYEM, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Wasteland_Rustboro_EventScript_SelinCaught
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, Wasteland_Rustboro_EventScript_SelinWonNotCaught
	releaseall
	end

Wasteland_Rustboro_EventScript_SelinNormal::
	msgbox Wasteland_Rustboro_Text_Selin, MSGBOX_DEFAULT
	release
	end

Wasteland_Rustboro_EventScript_SelinCaught::
	setflag FLAG_WASTELAND_RUSTBORO_PET_RESOLVED
	msgbox Wasteland_Rustboro_Text_SelinCaught, MSGBOX_DEFAULT
	goto Wasteland_Rustboro_EventScript_SelinReyesArrives

Wasteland_Rustboro_EventScript_SelinWonNotCaught::
	msgbox Wasteland_Rustboro_Text_SelinWonNotCaught, MSGBOX_DEFAULT
	givemon SPECIES_ELGYEM, 13
	goto_if_eq VAR_RESULT, 0, Wasteland_Rustboro_EventScript_SelinGaveElgyemParty
	goto_if_eq VAR_RESULT, 1, Wasteland_Rustboro_EventScript_SelinGaveElgyemPC
	goto_if_eq VAR_RESULT, 2, Wasteland_Rustboro_EventScript_SelinNoRoomForElgyem
	end

Wasteland_Rustboro_EventScript_SelinGaveElgyemParty::
	setflag FLAG_WASTELAND_RUSTBORO_PET_RESOLVED
	goto Wasteland_Rustboro_EventScript_SelinReyesArrives

Wasteland_Rustboro_EventScript_SelinGaveElgyemPC::
	setflag FLAG_WASTELAND_RUSTBORO_PET_RESOLVED
	msgbox Wasteland_Rustboro_Text_SelinElgyemSentToPC, MSGBOX_DEFAULT
	goto Wasteland_Rustboro_EventScript_SelinReyesArrives

Wasteland_Rustboro_EventScript_SelinNoRoomForElgyem::
	setflag FLAG_WASTELAND_RUSTBORO_PET_RESOLVED
	msgbox gText_NoMoreRoomForPokemon, MSGBOX_DEFAULT
	goto Wasteland_Rustboro_EventScript_SelinReyesArrives

Wasteland_Rustboro_EventScript_SelinAfter::
	msgbox Wasteland_Rustboro_Text_SelinAfter, MSGBOX_DEFAULT
	release
	end

@ Reyes' outdoor cutscene, new 2026-09-15, reworked same day (v4) after
@ Viktor reported her sprite looking broken/invisible and her exit walking
@ the wrong way. Two real problems, both fixed:
@ 1. She originally reused OBJ_EVENT_GFX_SCIENTIST_1 - the exact same
@    graphic the Scientist NPC (now standing right in this same crowd,
@    see the map.json note above his own script) uses, both on screen at
@    once. Switched to OBJ_EVENT_GFX_WOMAN_4 instead - confirmed via real
@    vanilla Emerald map usage (LilycoveCity_ContestHall, FortreeCity_
@    House4, etc. - not an FRLG-only sprite) and not used by anyone else
@    anywhere on this map, so there's no risk of two instances of the same
@    graphic being visible together again.
@ 2. The crowd (Selin/Man2/Scientist/LittleBoy/LittleGirl) packs the small
@    area right around the player too tightly for anyone else to walk
@    through cleanly - there was nowhere for her to arrive from or leave
@    toward without cutting through occupied tiles. Fixed by staging her
@    on the wide open street one row further south (confirmed via a full
@    collision dump: row 40, columns 9-21, is completely open) - she now
@    walks in from the east and leaves back east, which also reads as
@    "heading back toward the rest of the city" (the Gym itself is
@    further east) instead of vanishing south into nothing.
@ Object 16 in map.json (Wasteland_Rustboro_EventScript_ReyesArrivalDummy)
@ is permanently hidden via FLAG_WASTELAND_REYES_HIDDEN (set every map
@ load by Wasteland_Rustboro_OnTransition above) so she never passively
@ spawns; `addobject` here forces her in for this one scripted appearance
@ regardless of that flag - same one-shot-appearance idiom as Dad's own
@ exit sequence in the Safe Room.
Wasteland_Rustboro_EventScript_SelinReyesArrives::
	msgbox Wasteland_Rustboro_Text_SelinThatsAllThree, MSGBOX_DEFAULT
	@ Settling delay before spawning Reyes, in case reaching this point
	@ right after a real wild battle transition (rather than a direct
	@ script jump, which never showed any issue in testing) leaves the
	@ camera/object system mid-settle. Cheap, safe, best-effort defensive
	@ addition, not confirmed as the root cause of anything on its own.
	delay 30
	@ The crowd turns to look before she arrives - a small "everyone
	@ notices" flourish using objects already on screen, no extra object
	@ budget spent. Local IDs from events.inc: 6=LittleBoy, 7=LittleGirl,
	@ 11=Man2, 12=Scientist.
	@ IMPORTANT: `waitmovement 0` does NOT mean "wait for everyone" - per
	@ its own macro doc (asm/macros/event.inc), localId 0/LOCALID_NONE
	@ means "wait for whichever object was MOST RECENTLY applymovement'd."
	@ Calling applymovement 4 times then a single `waitmovement 0` only
	@ ever actually waited for the last one (LittleGirl) - the script was
	@ racing ahead of Reyes's own walk-in every time, which is almost
	@ certainly why her arrival looked broken/invisible: the dialogue box
	@ (covering the same screen area she walks through) was popping up
	@ before her movement had actually finished playing out, hiding it
	@ entirely. Fixed by waiting for each object explicitly by its own
	@ localId, never the ambiguous 0/"last-moved" shorthand.
	applymovement 11, Wasteland_Rustboro_Movement_CrowdNotices
	applymovement 12, Wasteland_Rustboro_Movement_CrowdNotices
	applymovement 6, Wasteland_Rustboro_Movement_CrowdNotices
	applymovement 7, Wasteland_Rustboro_Movement_CrowdNotices
	waitmovement 11
	waitmovement 12
	waitmovement 6
	waitmovement 7
	addobject 16
	applymovement 16, Wasteland_Rustboro_Movement_ReyesApproach
	waitmovement 16
	msgbox Wasteland_Rustboro_Text_ReyesArrival1, MSGBOX_DEFAULT
	msgbox Wasteland_Rustboro_Text_ReyesArrival2, MSGBOX_DEFAULT
	msgbox Wasteland_Rustboro_Text_ReyesArrival3, MSGBOX_DEFAULT
	msgbox Wasteland_Rustboro_Text_ReyesArrival4, MSGBOX_DEFAULT
	setflag FLAG_HAS_GYM_SPONSORSHIP
	msgbox Wasteland_Rustboro_Text_ReyesArrival5, MSGBOX_DEFAULT
	applymovement 16, Wasteland_Rustboro_Movement_ReyesLeave
	waitmovement 16
	removeobject 16
	releaseall
	end

Wasteland_Rustboro_Movement_CrowdNotices:
	face_right
	step_end

@ From (20,40) - the open street east of the crowd, confirmed clear via a
@ full collision dump - to (13,40), directly south of the player, facing
@ up toward the group. 7 tiles, matching the reverse exit below.
Wasteland_Rustboro_Movement_ReyesApproach:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	face_up
	step_end

@ Retraces the same open street east, back the way she came - reads as
@ heading back toward the rest of the city (the Gym is further east),
@ not vanishing off in a random direction.
Wasteland_Rustboro_Movement_ReyesLeave:
	face_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

Wasteland_Rustboro_EventScript_ReyesArrivalDummy::
	end

Wasteland_Rustboro_Text_Selin::
	.string "She won't come out from under the\n"
	.string "porch today. Won't even look at\l"
	.string "me.\p"
	.string "It's been like this since the\n"
	.string "alarm.$"

Wasteland_Rustboro_Text_SelinConverge1::
	.string "By the time you reach the house, a\n"
	.string "small crowd's already gathered - a\l"
	.string "maintenance drone circling low,\l"
	.string "some kind of display twitching in\l"
	.string "a shop window down the block.\p"
	.string "In the middle of it, Selin can't\n"
	.string "get her ELGYEM to stop screeching.$"

Wasteland_Rustboro_Text_SelinConverge2::
	.string "“About time,” Selin says. “Well?\n"
	.string "Do something!”$"

Wasteland_Rustboro_Text_SelinOneDown::
	.string "The drone drops out of the air,\n"
	.string "dead - whatever was driving it\l"
	.string "just... stopped.$"

Wasteland_Rustboro_Text_SelinTwoDown::
	.string "Two down. The crowd's gone quiet,\n"
	.string "watching.$"

Wasteland_Rustboro_Text_SelinAlert::
	.string "There - ! That's not her. She's\n"
	.string "never acted like this in nine\l"
	.string "years.\p"
	.string "Please - I don't know what else to\n"
	.string "do.$"

Wasteland_Rustboro_Text_SelinCaught::
	.string "You - caught her?\p"
	.string "I don't know whether to thank you\n"
	.string "or cry. Both, maybe.\p"
	.string "Take care of her. Whatever that\n"
	.string "alarm was, I don't think she's\l"
	.string "fully back.$"

Wasteland_Rustboro_Text_SelinWonNotCaught::
	.string "She's calm now. Calmer than she's\n"
	.string "been all day, actually - calmer\l"
	.string "than before, even.\p"
	.string "I don't think she's fully mine\n"
	.string "anymore. Not after that.\p"
	.string "Here. Please. I can't watch her go\n"
	.string "through that again, and I don't\l"
	.string "think I'm the one she trusts to\l"
	.string "stop it next time.$"

Wasteland_Rustboro_Text_SelinElgyemSentToPC::
	.string "There was no room in your party,\n"
	.string "so ELGYEM was sent to a Box at\l"
	.string "home.$"

Wasteland_Rustboro_Text_SelinThatsAllThree::
	.string "The crowd doesn't cheer, exactly.\n"
	.string "But nobody's panicking anymore\l"
	.string "either.\p"
	.string "Then you hear it - measured\n"
	.string "footsteps, cutting straight through\l"
	.string "the gathering.$"

Wasteland_Rustboro_Text_ReyesArrival1::
	.string "REYES: I heard that alarm cut out\n"
	.string "three times in under ten minutes.\l"
	.string "Had a guess who was behind it.$"

Wasteland_Rustboro_Text_ReyesArrival2::
	.string "Overseer Reyes. I run Assessment,\n"
	.string "for what that's worth today.\p"
	.string "Whatever's glitching the local\n"
	.string "relay, you handled it better than\l"
	.string "my own people did out there. That's\l"
	.string "not nothing.$"

Wasteland_Rustboro_Text_ReyesArrival3::
	.string "“Is there something Devon\n"
	.string "Corporation can do for you?” she\l"
	.string "asks. Not quite warmth. Not quite\l"
	.string "obligation either.$"

Wasteland_Rustboro_Text_ReyesArrival4::
	.string "You tell her all you want is a real\n"
	.string "shot at Assessment - the chance to\l"
	.string "challenge it properly, not talk\l"
	.string "your way past a guard.$"

Wasteland_Rustboro_Text_ReyesArrival5::
	.string "REYES: That's easy enough to\n"
	.string "arrange.\p"
	.string "Consider Assessment open for you -\n"
	.string "I'll clear it with the door myself.\l"
	.string "Go whenever you're ready.$"

Wasteland_Rustboro_Text_SelinAfter::
	.string "She's sleeping better with you\n"
	.string "around, I think. Or she just likes\l"
	.string "the company.$"
