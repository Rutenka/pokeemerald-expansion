Wasteland_Rustboro_Flat2_3F_MapScripts::
	.byte 0

@ Opened 2026-09-15, completing Flat2's upstairs per Viktor's request.
@ Reuses real vanilla RustboroCity_Flat2_3F verbatim - pure flavor, lightly
@ reworked from "the President collects rare stones" into a small,
@ deliberate note of quiet resentment about leadership living well while
@ everyone else rations, fitting the building's own established "Devon
@ workers live here" framing.
Wasteland_Rustboro_Flat2_3F_EventScript_Employee::
	lock
	faceplayer
	msgbox Wasteland_Rustboro_Flat2_3F_Text_Employee, MSGBOX_DEFAULT
	release
	end

Wasteland_Rustboro_Flat2_3F_EventScript_Woman::
	lock
	faceplayer
	msgbox Wasteland_Rustboro_Flat2_3F_Text_Woman, MSGBOX_DEFAULT
	release
	end

Wasteland_Rustboro_Flat2_3F_Text_Employee::
	.string "DEVON's President still collects\n"
	.string "rare stones. Has a whole case of\l"
	.string "them, I hear.\p"
	.string "Must be nice.$"

Wasteland_Rustboro_Flat2_3F_Text_Woman::
	.string "I heard the President's own family\n"
	.string "never went on ration schedules.\p"
	.string "Not once. Not even during the\n"
	.string "worst of it.$"
