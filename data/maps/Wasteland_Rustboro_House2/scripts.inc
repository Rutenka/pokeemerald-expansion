Wasteland_Rustboro_House2_MapScripts::
	.byte 0

@ Opened 2026-09-15. Reuses real vanilla RustboroCity_House2 verbatim.
@ Pure flavor - deliberately naive "Assessment is fair" civic pride,
@ reworked from vanilla's own "the Gym Leader is great" lines. Meant as
@ dramatic irony: the player already has the checkpoint ledger proving
@ Devon Corp arms the Ashband, so hearing ordinary residents genuinely
@ believe Assessment/the Overseer are just and benevolent lands very
@ differently for the player than for these two.
Wasteland_Rustboro_House2_EventScript_Woman::
	lock
	faceplayer
	msgbox Wasteland_Rustboro_House2_Text_Woman, MSGBOX_DEFAULT
	release
	end

Wasteland_Rustboro_House2_EventScript_LittleGirl::
	lock
	faceplayer
	msgbox Wasteland_Rustboro_House2_Text_LittleGirl, MSGBOX_DEFAULT
	release
	end

Wasteland_Rustboro_House2_Text_Woman::
	.string "Assessment's tough, but it's fair.\n"
	.string "That's what keeps this city\l"
	.string "running, if you ask me.$"

Wasteland_Rustboro_House2_Text_LittleGirl::
	.string "The OVERSEER's the strongest\n"
	.string "trainer in the whole city!\p"
	.string "My teacher says so, anyway.$"
