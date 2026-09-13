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

Wasteland_Rustboro_EventScript_Arrival::
	lockall
	msgbox Wasteland_Rustboro_Text_Arrival1, MSGBOX_DEFAULT
	closemessage
	msgbox Wasteland_Rustboro_Text_Arrival2, MSGBOX_DEFAULT
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

Wasteland_Rustboro_EventScript_Woman::
	lock
	faceplayer
	msgbox Wasteland_Rustboro_Text_Woman, MSGBOX_DEFAULT
	release
	end

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

Wasteland_Rustboro_EventScript_CorpGuard::
	lock
	faceplayer
	msgbox Wasteland_Rustboro_Text_CorpGuard, MSGBOX_DEFAULT
	release
	end

Wasteland_Rustboro_EventScript_DevonEmployee2::
	lock
	faceplayer
	msgbox Wasteland_Rustboro_Text_DevonEmployee2, MSGBOX_DEFAULT
	release
	end

Wasteland_Rustboro_EventScript_Man2::
	lock
	faceplayer
	msgbox Wasteland_Rustboro_Text_Man2, MSGBOX_DEFAULT
	release
	end

Wasteland_Rustboro_EventScript_Scientist::
	lock
	faceplayer
	msgbox Wasteland_Rustboro_Text_Scientist, MSGBOX_DEFAULT
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
	.string "Mostly ours.$"

Wasteland_Rustboro_Text_DevonEmployee2::
	.string "We don't call it a control network\n"
	.string "anymore. Corporate rebrand.\p"
	.string "“Coordination framework.” Feels\l"
	.string "completely different, I'm sure.$"

Wasteland_Rustboro_Text_Man2::
	.string "You get used to the drones after a\n"
	.string "while.\p"
	.string "They're not even armed. Probably.$"

Wasteland_Rustboro_Text_Scientist::
	.string "Please don't touch the equipment.\n"
	.string "It remembers.$"

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
