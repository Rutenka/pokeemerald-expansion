@ Reuses the real BattleFrontier_ReceptionGate layout verbatim for pure tile art
@ (a small north-south corridor building) - no gameplay from that facility carries
@ over. Reflavored as a border checkpoint between Miller's Cut and the corporate
@ city, per the checklist's "every non-connection transition should be a real,
@ visible door" rule - both ends are real doors (Miller's Cut's own real
@ MB_NORTH_ARROW_WARP mountain-pass tiles on one side, a plain door on the other),
@ no coord_event anywhere in the chain.
Wasteland_CorpCheckpoint_MapScripts::
	.byte 0

Wasteland_CorpCheckpoint_EventScript_Guard::
	lock
	faceplayer
	msgbox Wasteland_CorpCheckpoint_Text_Guard1, MSGBOX_DEFAULT
	msgbox Wasteland_CorpCheckpoint_Text_Guard2, MSGBOX_DEFAULT
	release
	end

Wasteland_CorpCheckpoint_Text_Guard1::
	.string "Halt. State your business in the\n"
	.string "administrative zone.\p"
	.string "…\n"
	.string "That's not one of the approved\l"
	.string "answers, but sure, whatever.$"

Wasteland_CorpCheckpoint_Text_Guard2::
	.string "Weapons, livestock, and unlicensed\n"
	.string "POKéMON abilities are all prohibited\l"
	.string "beyond this point.\p"
	.string "I don't make the list. I just stand\n"
	.string "here and say the list.$"
