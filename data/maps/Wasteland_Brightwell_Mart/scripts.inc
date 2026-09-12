@ Reuses the real, shared Mart interior (LAYOUT_MART) but deliberately has no
@ clerk and no shop trigger - per Viktor's decision (2026-09-12), this one
@ was raided and never came back online, unlike the Pokemon Center next door.
@ The empty counter and the scavenger's own line are what tell the player
@ that, rather than a shop menu that silently doesn't work - see CLAUDE.md's
@ world-building checklist on never leaving a normal-looking, functional-
@ looking fixture that quietly does nothing.
Wasteland_Brightwell_Mart_MapScripts::
	.byte 0

Wasteland_Brightwell_Mart_EventScript_Scavenger::
	lock
	faceplayer
	msgbox Wasteland_Brightwell_Mart_Text_Scavenger, MSGBOX_DEFAULT
	release
	end

Wasteland_Brightwell_Mart_Text_Scavenger::
	.string "Whoever hit this place knew what\n"
	.string "they wanted.\p"
	.string "Shelves picked clean. Register's\n"
	.string "gone. Even the back room's empty.\p"
	.string "Nothing left here worth taking.\n"
	.string "Believe me, I looked first.$"
