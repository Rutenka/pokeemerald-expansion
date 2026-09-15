Wasteland_Rustboro_House3_MapScripts::
	.byte 0

@ Opened 2026-09-15. Reuses real vanilla RustboroCity_House3 verbatim,
@ keeping its "elderly couple with a found pet" structure but reworked
@ into something that fits this story directly - a small, deliberate
@ "hope alongside institutional cruelty" beat (per the design brief's own
@ stated principle) rather than vanilla's pure joke about a misspelled
@ Pikachu nickname. The decorative pet is OBJ_EVENT_GFX_ZIGZAGOON_2
@ (confirmed real non-FRLG usage in FortreeCity_House1) instead of
@ Pikachu, matching a species already on this project's own roster.
Wasteland_Rustboro_House3_EventScript_OldMan::
	lock
	faceplayer
	msgbox Wasteland_Rustboro_House3_Text_OldMan, MSGBOX_DEFAULT
	release
	end

Wasteland_Rustboro_House3_EventScript_OldWoman::
	lock
	faceplayer
	msgbox Wasteland_Rustboro_House3_Text_OldWoman, MSGBOX_DEFAULT
	release
	end

Wasteland_Rustboro_House3_EventScript_Pet::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ZIGZAGOON, CRY_MODE_NORMAL
	msgbox Wasteland_Rustboro_House3_Text_Pet, MSGBOX_DEFAULT
	waitmoncry
	release
	end

Wasteland_Rustboro_House3_Text_OldMan::
	.string "She showed up on the porch about a\n"
	.string "year back. No collar, no chip,\l"
	.string "nothing.\p"
	.string "We figured whoever she belonged to\n"
	.string "didn't make it through everything\l"
	.string "that happened.$"

Wasteland_Rustboro_House3_Text_OldWoman::
	.string "We call her FRECKLE. She still\n"
	.string "waits by the door most evenings.\p"
	.string "Old habits, I suppose. Same as\n"
	.string "the rest of us.$"

Wasteland_Rustboro_House3_Text_Pet::
	.string "FRECKLE: Zig!$"
