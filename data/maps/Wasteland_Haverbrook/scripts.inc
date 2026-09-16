@ Reuses the real, whole vanilla PetalburgCity layout verbatim (per the
@ standing "no crop-and-stitch, reskin only" rule). Territory 3 of the
@ confirmed 8-territory story spine (CLAUDE.md's Thirty-first feature
@ entry): an independent trading settlement, no warlord, no corporation -
@ the first "Pokemon partnership is good" beat after two "everyone's
@ compromised" chapters. Wally's own cutscene pair and Scott were dropped
@ (vanilla-specific content not relevant here); Wally's House, House1, and
@ House2's real doors are deliberately left unwired for now, same "closed
@ for now" trade-off used throughout this project.
@
@ Reached via Wasteland_EastRoad's real cave-mouth door (not a map
@ connection - see the Thirty-fifth feature entry in CLAUDE.md for why
@ the original Wasteland_SouthRoad/connection approach was retired).
@ warp_events[3] at (17,18) is the landing spot; the return trip is a
@ coord_event one tile away at (16,18), same "landing != trigger" pattern
@ used everywhere else in this project.
Wasteland_Haverbrook_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Wasteland_Haverbrook_OnTransition
	.byte 0

Wasteland_Haverbrook_OnTransition:
	setrespawn HEAL_LOCATION_WASTELAND_HAVERBROOK
	end

Wasteland_Haverbrook_EventScript_ExitToEastRoad::
	warp MAP_WASTELAND_EAST_ROAD, 1
	waitstate
	end

Wasteland_Haverbrook_EventScript_Arrival::
	setflag FLAG_SEEN_HAVERBROOK_ARRIVAL
	lockall
	msgbox Wasteland_Haverbrook_Text_Arrival, MSGBOX_DEFAULT
	releaseall
	end

Wasteland_Haverbrook_Text_Arrival::
	.string "No cameras. No badge checks. No\n"
	.string "one asking for your business here.\p"
	.string "Haverbrook runs on trade and\n"
	.string "trust, not clearance - and somehow\l"
	.string "that's kept it standing this long.\p"
	.string "Garrick's the one who's made sure\n"
	.string "of it. Everyone here says so, one\l"
	.string "way or another.$"

Wasteland_Haverbrook_EventScript_Mara::
	lock
	faceplayer
	msgbox Wasteland_Haverbrook_Text_Mara, MSGBOX_DEFAULT
	release
	end

Wasteland_Haverbrook_Text_Mara::
	.string "We don't ask where people came\n"
	.string "from here. Doesn't matter, as long\l"
	.string "as you pull your weight.$"

Wasteland_Haverbrook_EventScript_Boy::
	lock
	faceplayer
	msgbox Wasteland_Haverbrook_Text_Boy, MSGBOX_DEFAULT
	release
	end

Wasteland_Haverbrook_Text_Boy::
	.string "Garrick let me hold his Miltank's\n"
	.string "lead once. Best day of my life,\l"
	.string "honestly.$"

Wasteland_Haverbrook_EventScript_Trader::
	lock
	faceplayer
	msgbox Wasteland_Haverbrook_Text_Trader, MSGBOX_DEFAULT
	release
	end

Wasteland_Haverbrook_Text_Trader::
	.string "Rustboro sends what it can spare.\n"
	.string "We send back what they can't grow\l"
	.string "themselves. Fair trade, so far.$"

Wasteland_Haverbrook_EventScript_ProvingGroundsGuide::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_HAVERBROOK_PROTECTOR, Wasteland_Haverbrook_EventScript_GuideAfter
	msgbox Wasteland_Haverbrook_Text_GuideBefore, MSGBOX_DEFAULT
	release
	end

Wasteland_Haverbrook_EventScript_GuideAfter::
	msgbox Wasteland_Haverbrook_Text_GuideAfter, MSGBOX_DEFAULT
	release
	end

Wasteland_Haverbrook_Text_GuideBefore::
	.string "Garrick trains behind that door.\n"
	.string "Doesn't turn anyone away who asks\l"
	.string "honestly - but he won't go easy on\l"
	.string "you either.$"

Wasteland_Haverbrook_Text_GuideAfter::
	.string "Word's already gotten around about\n"
	.string "your match. Garrick doesn't lose\l"
	.string "often.$"

Wasteland_Haverbrook_EventScript_ProvingGroundsSign::
	msgbox Wasteland_Haverbrook_Text_ProvingGroundsSign, MSGBOX_SIGN
	end

Wasteland_Haverbrook_Text_ProvingGroundsSign::
	.string "THE PROVING GROUNDS - all comers\n"
	.string "welcome, on foot or with a team.$"

Wasteland_Haverbrook_EventScript_CitySign::
	msgbox Wasteland_Haverbrook_Text_CitySign, MSGBOX_SIGN
	end

Wasteland_Haverbrook_Text_CitySign::
	.string "HAVERBROOK - self-governed since\n"
	.string "before anyone here can remember\l"
	.string "why it needed to be.$"
