Wasteland_Port_Registrar_MapScripts::
	.byte 0

Wasteland_Port_Registrar_EventScript_Registrar::
	lock
	faceplayer
	goto_if_set FLAG_WASTELAND_PORT_REGISTERED, Wasteland_Port_Registrar_EventScript_Already
	msgbox Wasteland_Port_Registrar_Text_Register, MSGBOX_DEFAULT
	setflag FLAG_WASTELAND_PORT_REGISTERED
	msgbox Wasteland_Port_Registrar_Text_Filed, MSGBOX_DEFAULT
	release
	end

Wasteland_Port_Registrar_EventScript_Already::
	msgbox Wasteland_Port_Registrar_Text_Already, MSGBOX_DEFAULT
	release
	end

Wasteland_Port_Registrar_Text_Register::
	.string "Registration. Name, origin,\n"
	.string "purpose. In that order. Please\l"
	.string "don't skip any.\p"
	.string "Name? Smith. Lovely. Everyone's a\n"
	.string "Smith this year.\p"
	.string "Origin? North. Purpose? Passing\n"
	.string "through. Wonderful. That's all\l"
	.string "three.$"

Wasteland_Port_Registrar_Text_Filed::
	.string "You're filed. The guards at the\n"
	.string "hall have been told to let you\l"
	.string "through.\p"
	.string "Stay out of the harbor after\n"
	.string "dark. It isn't a rule. It's just\l"
	.string "a thing.$"

Wasteland_Port_Registrar_Text_Already::
	.string "You're on file. That's better\n"
	.string "than most. Come back if you need\l"
	.string "anything filed.$"

