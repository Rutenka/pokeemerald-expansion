Wasteland_Rustboro_Flat2_2F_MapScripts::
	.byte 0

@ Opened 2026-09-15, completing Flat2's upstairs per Viktor's request.
@ Reuses real vanilla RustboroCity_Flat2_2F verbatim, keeping its real
@ item giveaway (a free PREMIER BALL) since it's a genuinely nice small
@ gift, not just flavor.
Wasteland_Rustboro_Flat2_2F_EventScript_OldMan::
	lock
	faceplayer
	msgbox Wasteland_Rustboro_Flat2_2F_Text_OldMan, MSGBOX_DEFAULT
	release
	end

Wasteland_Rustboro_Flat2_2F_EventScript_Boy::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_PREMIER_BALL_RUSTBORO, Wasteland_Rustboro_Flat2_2F_EventScript_BoyAfter
	msgbox Wasteland_Rustboro_Flat2_2F_Text_BoyGivesBall, MSGBOX_DEFAULT
	giveitem ITEM_PREMIER_BALL
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_PREMIER_BALL_RUSTBORO
	release
	end

Wasteland_Rustboro_Flat2_2F_EventScript_BoyAfter::
	msgbox Wasteland_Rustboro_Flat2_2F_Text_BoyAfter, MSGBOX_DEFAULT
	release
	end

Wasteland_Rustboro_Flat2_2F_Text_OldMan::
	.string "Way back before all this, DEVON was\n"
	.string "just a teeny, tiny company.$"

Wasteland_Rustboro_Flat2_2F_Text_BoyGivesBall::
	.string "My dad's working at the\n"
	.string "CORPORATION.\p"
	.string "He made this! But I can't use it,\n"
	.string "so you can have it.$"

Wasteland_Rustboro_Flat2_2F_Text_BoyAfter::
	.string "My dad's working at the\n"
	.string "CORPORATION.\p"
	.string "When I grow up, I'm going to work\n"
	.string "for DEVON too. Everyone says\l"
	.string "that's the safe thing to do.$"
