@ A real, whole, unmodified house interior (LAYOUT_HOUSE1, the same shared
@ layout Verdanturf's own "House" uses) behind one of Brightwell's real doors
@ ((17,15), reused from VerdanturfTown's own data) - reskinned only with a new
@ NPC and dialogue, per the "whole real maps, no cropping" rule.
Wasteland_Brightwell_House_MapScripts::
	.byte 0

Wasteland_Brightwell_House_EventScript_Woman::
	lock
	faceplayer
	msgbox Wasteland_Brightwell_House_Text_Woman, MSGBOX_DEFAULT
	release
	end

Wasteland_Brightwell_House_Text_Woman::
	.string "I keep the door locked now. Didn't\n"
	.string "used to.\p"
	.string "The boy by the well - his mother\n"
	.string "worked the checkpoint. She hasn't\l"
	.string "come back either.\p"
	.string "I feed him when I can. Nobody's in\n"
	.string "charge of anything anymore, so I\l"
	.string "suppose that makes it my job.$"
