Wasteland_Crossing_MapScripts::
	.byte 0

Wasteland_Crossing_EventScript_Keeper::
	lock
	faceplayer
	msgbox Wasteland_Crossing_Text_Keeper, MSGBOX_DEFAULT
	release
	end

Wasteland_Crossing_Text_Keeper::
	.string "Welcome to the Crossing.\n"
	.string "Population, whoever's here.\p"
	.string "Toll for onward travel is one\n"
	.string "mild inconvenience. There. Paid.\p"
	.string "Enjoy the Shore Road.$"

Wasteland_Crossing_EventScript_Girl::
	lock
	faceplayer
	msgbox Wasteland_Crossing_Text_Girl, MSGBOX_DEFAULT
	release
	end

Wasteland_Crossing_Text_Girl::
	.string "My brother went north on one of\n"
	.string "the company trucks to earn his\l"
	.string "keep. That was two winters ago.\l"
	.string "They said he'd write.$"

Wasteland_Crossing_EventScript_Clerk::
	lock
	faceplayer
	msgbox Wasteland_Crossing_Text_Clerk, MSGBOX_DEFAULT
	release
	end

Wasteland_Crossing_Text_Clerk::
	.string "Closed. Nobody's restocked since\n"
	.string "the wardens started taking the\l"
	.string "deliveries. Come back when the\l"
	.string "world's tidier.$"

Wasteland_Crossing_EventScript_Maniac::
	lock
	faceplayer
	msgbox Wasteland_Crossing_Text_Maniac, MSGBOX_DEFAULT
	release
	end

Wasteland_Crossing_Text_Maniac::
	.string "Trucks come through at night.\n"
	.string "Heavy, no markings, no lights.\l"
	.string "They go north empty and come back\l"
	.string "heavier.\p"
	.string "I count the wheels. Somebody\n"
	.string "should count.$"

Wasteland_Crossing_EventScript_TownSign::
	msgbox Wasteland_Crossing_Text_TownSign, MSGBOX_SIGN
	end

Wasteland_Crossing_Text_TownSign::
	.string "THE CROSSING: where the road pays\n"
	.string "for itself.$"

