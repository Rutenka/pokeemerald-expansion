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

Wasteland_Rustboro_EventScript_Woman::
	lock
	faceplayer
	msgbox Wasteland_Rustboro_Text_Woman, MSGBOX_DEFAULT
	release
	end

@ Side quest, first version (2026-09-14): the Gym is locked behind a
@ sponsorship a guard checks for, earned from FatMan/DevonEmployee2. Viktor
@ asked for more weight than a plain fetch-quest - "help them with
@ something... get ignored, then something happens, then earn their trust" -
@ so this is now the front door of a 3-part incident (see the drone/
@ artifact/pet encounters below) rather than a single conversation. FatMan
@ dismisses the player outright on first talk; that dismissal is what the
@ incident interrupts. No new map, no new trainer (the 9-slot custom
@ trainer budget is fully spent - see docs/roster.md) - three real
@ `wildbattle` encounters instead, which don't touch that budget at all.
Wasteland_Rustboro_EventScript_FatMan::
	lock
	faceplayer
	goto_if_set FLAG_HAS_MISFILED_PAPERWORK, Wasteland_Rustboro_EventScript_FatManAfter
	goto_if_set FLAG_WASTELAND_RUSTBORO_INCIDENT_STARTED, Wasteland_Rustboro_EventScript_FatManIncidentCheck
	msgbox Wasteland_Rustboro_Text_FatMan, MSGBOX_DEFAULT
	msgbox Wasteland_Rustboro_Text_FatManDismissal, MSGBOX_DEFAULT
	setflag FLAG_WASTELAND_RUSTBORO_INCIDENT_STARTED
	msgbox Wasteland_Rustboro_Text_IncidentAlarm, MSGBOX_DEFAULT
	release
	end

Wasteland_Rustboro_EventScript_FatManIncidentCheck::
	goto_if_unset FLAG_WASTELAND_RUSTBORO_DRONE_RESOLVED, Wasteland_Rustboro_EventScript_FatManStillBusy
	goto_if_unset FLAG_WASTELAND_RUSTBORO_ARTIFACT_RESOLVED, Wasteland_Rustboro_EventScript_FatManStillBusy
	goto_if_unset FLAG_WASTELAND_RUSTBORO_PET_RESOLVED, Wasteland_Rustboro_EventScript_FatManStillBusy
	msgbox Wasteland_Rustboro_Text_FatManImpressed, MSGBOX_DEFAULT
	msgbox Wasteland_Rustboro_Text_FatManGivesPaperwork, MSGBOX_DEFAULT
	setflag FLAG_HAS_MISFILED_PAPERWORK
	release
	end

Wasteland_Rustboro_EventScript_FatManStillBusy::
	msgbox Wasteland_Rustboro_Text_FatManStillBusy, MSGBOX_DEFAULT
	release
	end

Wasteland_Rustboro_EventScript_FatManAfter::
	msgbox Wasteland_Rustboro_Text_FatManAfter, MSGBOX_DEFAULT
	release
	end

Wasteland_Rustboro_EventScript_NinjaBoy::
	lock
	faceplayer
	msgbox Wasteland_Rustboro_Text_NinjaBoy, MSGBOX_DEFAULT
	release
	end

Wasteland_Rustboro_EventScript_Twin::
	lock
	faceplayer
	msgbox Wasteland_Rustboro_Text_Twin, MSGBOX_DEFAULT
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

Wasteland_Rustboro_EventScript_LittleBoy::
	lock
	faceplayer
	msgbox Wasteland_Rustboro_Text_LittleBoy, MSGBOX_DEFAULT
	release
	end

Wasteland_Rustboro_EventScript_LittleGirl::
	lock
	faceplayer
	msgbox Wasteland_Rustboro_Text_LittleGirl, MSGBOX_DEFAULT
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

Wasteland_Rustboro_EventScript_DevonEmployee2::
	lock
	faceplayer
	msgbox Wasteland_Rustboro_Text_DevonEmployee2, MSGBOX_DEFAULT
	goto_if_set FLAG_HAS_GYM_SPONSORSHIP, Wasteland_Rustboro_EventScript_DevonEmployee2Sponsored
	goto_if_set FLAG_HAS_MISFILED_PAPERWORK, Wasteland_Rustboro_EventScript_DevonEmployee2GiveSponsorship
	msgbox Wasteland_Rustboro_Text_DevonEmployee2AskFavor, MSGBOX_DEFAULT
	release
	end

Wasteland_Rustboro_EventScript_DevonEmployee2GiveSponsorship::
	msgbox Wasteland_Rustboro_Text_DevonEmployee2Thanks, MSGBOX_DEFAULT
	setflag FLAG_HAS_GYM_SPONSORSHIP
	release
	end

Wasteland_Rustboro_EventScript_DevonEmployee2Sponsored::
	release
	end

@ Incident site 1 of 3 (2026-09-14) - Man2's own original line ("You get used
@ to the drones... they're not even armed. Probably.") already foreshadowed
@ this. A real `wildbattle` (Voltorb), not a trainer - the custom trainer ID
@ budget is fully spent (docs/roster.md).
Wasteland_Rustboro_EventScript_Man2::
	lock
	faceplayer
	goto_if_unset FLAG_WASTELAND_RUSTBORO_INCIDENT_STARTED, Wasteland_Rustboro_EventScript_Man2Normal
	goto_if_set FLAG_WASTELAND_RUSTBORO_DRONE_RESOLVED, Wasteland_Rustboro_EventScript_Man2AfterDrone
	msgbox Wasteland_Rustboro_Text_Man2DroneAlert, MSGBOX_DEFAULT
	setwildbattle SPECIES_VOLTORB, 13, ITEM_NONE
	waitse
	playmoncry SPECIES_VOLTORB, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, Wasteland_Rustboro_EventScript_Man2DroneWon
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Wasteland_Rustboro_EventScript_Man2DroneWon
	release
	end

Wasteland_Rustboro_EventScript_Man2Normal::
	msgbox Wasteland_Rustboro_Text_Man2, MSGBOX_DEFAULT
	release
	end

Wasteland_Rustboro_EventScript_Man2DroneWon::
	setflag FLAG_WASTELAND_RUSTBORO_DRONE_RESOLVED
	msgbox Wasteland_Rustboro_Text_Man2DroneWon, MSGBOX_DEFAULT
	release
	end

Wasteland_Rustboro_EventScript_Man2AfterDrone::
	msgbox Wasteland_Rustboro_Text_Man2AfterDrone, MSGBOX_DEFAULT
	release
	end

@ Incident site 2 of 3 (2026-09-14) - the Scientist's own original line
@ ("Please don't touch the equipment. It remembers.") already foreshadowed
@ this directly. A real `wildbattle` (Baltoy), same reasoning as Man2 above.
Wasteland_Rustboro_EventScript_Scientist::
	lock
	faceplayer
	goto_if_unset FLAG_WASTELAND_RUSTBORO_INCIDENT_STARTED, Wasteland_Rustboro_EventScript_ScientistNormal
	goto_if_set FLAG_WASTELAND_RUSTBORO_ARTIFACT_RESOLVED, Wasteland_Rustboro_EventScript_ScientistAfterArtifact
	msgbox Wasteland_Rustboro_Text_ScientistArtifactAlert, MSGBOX_DEFAULT
	setwildbattle SPECIES_BALTOY, 13, ITEM_NONE
	waitse
	playmoncry SPECIES_BALTOY, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, Wasteland_Rustboro_EventScript_ScientistArtifactWon
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Wasteland_Rustboro_EventScript_ScientistArtifactWon
	release
	end

Wasteland_Rustboro_EventScript_ScientistNormal::
	msgbox Wasteland_Rustboro_Text_Scientist, MSGBOX_DEFAULT
	release
	end

Wasteland_Rustboro_EventScript_ScientistArtifactWon::
	setflag FLAG_WASTELAND_RUSTBORO_ARTIFACT_RESOLVED
	msgbox Wasteland_Rustboro_Text_ScientistArtifactWon, MSGBOX_DEFAULT
	release
	end

Wasteland_Rustboro_EventScript_ScientistAfterArtifact::
	msgbox Wasteland_Rustboro_Text_ScientistAfterArtifact, MSGBOX_DEFAULT
	release
	end

Wasteland_Rustboro_EventScript_Boy1::
	lock
	faceplayer
	msgbox Wasteland_Rustboro_Text_Boy1, MSGBOX_DEFAULT
	release
	end

Wasteland_Rustboro_EventScript_ItemFullRestore::
	finditem ITEM_FULL_RESTORE

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
	.string "as I can tell. I file them anyway.$"

Wasteland_Rustboro_Text_FatManDismissal::
	.string "And no, I can't help you. I don't\n"
	.string "have clearance to help people who\l"
	.string "just “wandered in.”\p"
	.string "Take it up with Coordination. Or\n"
	.string "don't. Not my problem either way.$"

Wasteland_Rustboro_Text_IncidentAlarm::
	.string "Somewhere across the district, an\n"
	.string "alarm starts - short, rising, cut\l"
	.string "off mid-note.\p"
	.string "Nobody in the office even looks\n"
	.string "up. Like they were waiting for it.$"

Wasteland_Rustboro_Text_FatManStillBusy::
	.string "Still can't help you. District's a\n"
	.string "mess right now - people all over the\l"
	.string "block reporting Pokémon behaving\l"
	.string "wrong, and nobody up top's saying\l"
	.string "why.\p"
	.string "Sort that out first. Then we'll\n"
	.string "talk.$"

Wasteland_Rustboro_Text_FatManImpressed::
	.string "Word travels. Drone on Ash Row, the\n"
	.string "Study Hall thing, and now Selin's\l"
	.string "bird.\p"
	.string "Didn't expect an outsider to\n"
	.string "actually deal with any of it.\l"
	.string "Didn't expect anyone to, honestly.$"

Wasteland_Rustboro_Text_FatManGivesPaperwork::
	.string "…Actually, hold on.\p"
	.string "This authorization's been sitting in\n"
	.string "my tray for two weeks. Not mine.\l"
	.string "Somebody in Coordination's, by the\l"
	.string "stamp.\p"
	.string "Here. Don't lose it a second time.$"

Wasteland_Rustboro_Text_FatManAfter::
	.string "Try not to lose it this time.$"

Wasteland_Rustboro_Text_NinjaBoy::
	.string "They test us for “aptitude” now.\n"
	.string "I scored high in obedience.\p"
	.string "I'm still not sure that's supposed\l"
	.string "to be a compliment.$"

Wasteland_Rustboro_Text_Twin::
	.string "My sister and I get the same\n"
	.string "rations. The same schooling.\p"
	.string "It's supposed to feel fair.\l"
	.string "Mostly it just feels counted.$"

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

Wasteland_Rustboro_Text_DevonEmployee2AskFavor::
	.string "Trying to get into Assessment?\n"
	.string "I could vouch for you - I've got the\l"
	.string "standing.\p"
	.string "Except my own authorization's sat\n"
	.string "“unfiled” in Records for two weeks.\l"
	.string "Ask for the big fellow down there.\l"
	.string "Ironic - he's the one clerk who\l"
	.string "actually reads what crosses his desk.$"

Wasteland_Rustboro_Text_DevonEmployee2Thanks::
	.string "There it is. Knew it wasn't lost -\n"
	.string "just filed somewhere useless.\p"
	.string "I'll let the door know you're\n"
	.string "sponsored. Go on, then.$"

Wasteland_Rustboro_Text_Man2::
	.string "You get used to the drones after a\n"
	.string "while.\p"
	.string "They're not even armed. Probably.$"

Wasteland_Rustboro_Text_Man2DroneAlert::
	.string "That drone's not on its usual\n"
	.string "loop.\p"
	.string "Its eye just… locked on you.\n"
	.string "Get ready!$"

Wasteland_Rustboro_Text_Man2DroneWon::
	.string "It just… stopped. Like someone cut\n"
	.string "the signal mid-command.\p"
	.string "Six years on this block. Never\n"
	.string "seen one do that before today.$"

Wasteland_Rustboro_Text_Man2AfterDrone::
	.string "Maintenance hauled it off this\n"
	.string "morning.\p"
	.string "Nobody's explaining anything.\n"
	.string "Same as always.$"

Wasteland_Rustboro_Text_Scientist::
	.string "Please don't touch the equipment.\n"
	.string "It remembers.$"

Wasteland_Rustboro_Text_ScientistArtifactAlert::
	.string "I told you - it remembers!\p"
	.string "It's not supposed to move on its\n"
	.string "own. Someone's still transmitting\l"
	.string "to it - !$"

Wasteland_Rustboro_Text_ScientistArtifactWon::
	.string "Whatever was steering it let go\n"
	.string "the second you won.\p"
	.string "I should write this up. I already\n"
	.string "know nobody upstairs wants it\l"
	.string "written up.$"

Wasteland_Rustboro_Text_ScientistAfterArtifact::
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

@ Blocks the Gym door until FLAG_HAS_GYM_SPONSORSHIP is set (see
@ DevonEmployee2/FatMan above) - the guard's own object_event "flag" field
@ hides him automatically once that flag is set, same proven mechanism as
@ the Miller's Cut blockade.
Wasteland_Rustboro_EventScript_GymGuard::
	msgbox Wasteland_Rustboro_Text_GymGuard, MSGBOX_NPC
	end

Wasteland_Rustboro_Text_GymGuard::
	.string "No Assessment without sponsorship.\n"
	.string "Talk to someone with real standing\l"
	.string "in this city. Not me.$"

@ Incident site 3 of 3, the capstone (2026-09-14) - Selin's own Natu, the
@ one living creature in this incident rather than a drone or an artifact,
@ deliberately given more weight - and the one the player can keep
@ afterward (Viktor's ask: a catchable reward that fits the story and the
@ early game). A real `wildbattle`, same reasoning as the other two sites -
@ if the player catches it themselves during the fight, no separate gift is
@ needed; if they win without catching it, Selin gives it to them directly
@ afterward via `givemon`, using the same party/PC/no-room branching as the
@ Safe Room's own starter gift.
Wasteland_Rustboro_EventScript_Selin::
	lock
	faceplayer
	goto_if_unset FLAG_WASTELAND_RUSTBORO_INCIDENT_STARTED, Wasteland_Rustboro_EventScript_SelinNormal
	goto_if_set FLAG_WASTELAND_RUSTBORO_PET_RESOLVED, Wasteland_Rustboro_EventScript_SelinAfter
	msgbox Wasteland_Rustboro_Text_SelinAlert, MSGBOX_DEFAULT
	setwildbattle SPECIES_NATU, 13, ITEM_NONE
	waitse
	playmoncry SPECIES_NATU, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Wasteland_Rustboro_EventScript_SelinCaught
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, Wasteland_Rustboro_EventScript_SelinWonNotCaught
	release
	end

Wasteland_Rustboro_EventScript_SelinNormal::
	msgbox Wasteland_Rustboro_Text_Selin, MSGBOX_DEFAULT
	release
	end

Wasteland_Rustboro_EventScript_SelinCaught::
	setflag FLAG_WASTELAND_RUSTBORO_PET_RESOLVED
	msgbox Wasteland_Rustboro_Text_SelinCaught, MSGBOX_DEFAULT
	release
	end

Wasteland_Rustboro_EventScript_SelinWonNotCaught::
	msgbox Wasteland_Rustboro_Text_SelinWonNotCaught, MSGBOX_DEFAULT
	givemon SPECIES_NATU, 13
	goto_if_eq VAR_RESULT, 0, Wasteland_Rustboro_EventScript_SelinGaveNatuParty
	goto_if_eq VAR_RESULT, 1, Wasteland_Rustboro_EventScript_SelinGaveNatuPC
	goto_if_eq VAR_RESULT, 2, Wasteland_Rustboro_EventScript_SelinNoRoomForNatu
	end

Wasteland_Rustboro_EventScript_SelinGaveNatuParty::
	setflag FLAG_WASTELAND_RUSTBORO_PET_RESOLVED
	release
	end

Wasteland_Rustboro_EventScript_SelinGaveNatuPC::
	setflag FLAG_WASTELAND_RUSTBORO_PET_RESOLVED
	msgbox Wasteland_Rustboro_Text_SelinNatuSentToPC, MSGBOX_DEFAULT
	release
	end

Wasteland_Rustboro_EventScript_SelinNoRoomForNatu::
	setflag FLAG_WASTELAND_RUSTBORO_PET_RESOLVED
	msgbox gText_NoMoreRoomForPokemon, MSGBOX_DEFAULT
	release
	end

Wasteland_Rustboro_EventScript_SelinAfter::
	msgbox Wasteland_Rustboro_Text_SelinAfter, MSGBOX_DEFAULT
	release
	end

Wasteland_Rustboro_Text_Selin::
	.string "She won't come down off the awning\n"
	.string "today. Won't even look at me.\p"
	.string "It's been like this since the\n"
	.string "alarm.$"

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

Wasteland_Rustboro_Text_SelinNatuSentToPC::
	.string "There was no room in your party,\n"
	.string "so NATU was sent to a Box at home.$"

Wasteland_Rustboro_Text_SelinAfter::
	.string "She's sleeping better with you\n"
	.string "around, I think. Or she just likes\l"
	.string "the company.$"
