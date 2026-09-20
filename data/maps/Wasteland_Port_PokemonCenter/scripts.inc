@ Shared Pokemon Center interior, same simplified heal flow as Haverbrook's.
Wasteland_Port_PokemonCenter_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Wasteland_Port_PokemonCenter_OnTransition
	.byte 0

Wasteland_Port_PokemonCenter_OnTransition:
	setrespawn HEAL_LOCATION_WASTELAND_PORT
	end

Wasteland_Port_PokemonCenter_EventScript_Nurse::
	lock
	faceplayer
	msgbox Wasteland_Port_PokemonCenter_Text_Heal, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Wasteland_Port_PokemonCenter_EventScript_No
	message Wasteland_Port_PokemonCenter_Text_OneMoment
	waitmessage
	special HealPlayerParty
	msgbox Wasteland_Port_PokemonCenter_Text_Done, MSGBOX_DEFAULT
	release
	end

Wasteland_Port_PokemonCenter_EventScript_No::
	msgbox Wasteland_Port_PokemonCenter_Text_No, MSGBOX_DEFAULT
	release
	end

Wasteland_Port_PokemonCenter_Text_Heal::
	.string "Everyone gets patched up here,\n"
	.string "raider or not. It's on the\l"
	.string "register either way. Shall I?$"

Wasteland_Port_PokemonCenter_Text_OneMoment::
	.string "One moment. I'll log the visit.$"

Wasteland_Port_PokemonCenter_Text_Done::
	.string "Done. Your team's in better shape\n"
	.string "than the harbor.$"

Wasteland_Port_PokemonCenter_Text_No::
	.string "Noted. The door's open.$"

