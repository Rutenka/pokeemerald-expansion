Wasteland_Rustboro_CuttersHouse_MapScripts::
	.byte 0

@ Opened 2026-09-15. Reuses real vanilla RustboroCity_CuttersHouse
@ verbatim, keeping its real mechanic (a free HM CUT) since it's genuinely
@ useful, not just flavor - reframed as a practical survival tool (salvage
@ access) rather than vanilla's decorative hedge-trimming framing.
@ IMPORTANT: HM field moves are gated on the matching badge flag
@ (src/field_move.c, FLAG_BADGE01_GET for Cut) - since this story has no
@ gym badges, that flag is granted directly by actually beating the
@ Overseer (Wasteland_RustboroGym/scripts.inc), not by anything here, so
@ Cut is only usable in the field once the player has genuinely cleared
@ Assessment - matching real vanilla's own logic (the badge comes from
@ winning the Gym fight, not from being let through the door) without
@ blocking the player from receiving the HM itself beforehand.
Wasteland_Rustboro_CuttersHouse_EventScript_Cutter::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM_CUT, Wasteland_Rustboro_CuttersHouse_EventScript_ExplainCut
	msgbox Wasteland_Rustboro_CuttersHouse_Text_TakeThisHM, MSGBOX_DEFAULT
	giveitem ITEM_HM_CUT
	goto_if_eq VAR_RESULT, 0, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_HM_CUT
	msgbox Wasteland_Rustboro_CuttersHouse_Text_ExplainCut, MSGBOX_DEFAULT
	release
	end

Wasteland_Rustboro_CuttersHouse_EventScript_ExplainCut::
	msgbox Wasteland_Rustboro_CuttersHouse_Text_ExplainCut, MSGBOX_DEFAULT
	release
	end

Wasteland_Rustboro_CuttersHouse_EventScript_Daughter::
	lock
	faceplayer
	msgbox Wasteland_Rustboro_CuttersHouse_Text_Daughter, MSGBOX_DEFAULT
	release
	end

Wasteland_Rustboro_CuttersHouse_Text_TakeThisHM::
	.string "Before, this was decorative work.\n"
	.string "Trimming hedges, that sort of\l"
	.string "thing.\p"
	.string "Now it's how you get into buildings\n"
	.string "nobody's opened in years.\p"
	.string "Here - my POKéMON and I don't need\n"
	.string "two of these.$"

Wasteland_Rustboro_CuttersHouse_Text_ExplainCut::
	.string "That's HM CUT. Unlike a TM, it can\n"
	.string "be used more than once.\p"
	.string "Once you've actually got standing\n"
	.string "in this city - not just talked your\l"
	.string "way in - your POKéMON will use it\l"
	.string "outside of battle too.$"

Wasteland_Rustboro_CuttersHouse_Text_Daughter::
	.string "Dad says CUT used to be for\n"
	.string "trimming hedges.\p"
	.string "Now everyone wants to borrow him\n"
	.string "for salvage runs.$"
