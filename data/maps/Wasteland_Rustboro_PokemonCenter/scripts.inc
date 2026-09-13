@ The real, shared Pokemon Center interior + the engine's own healing flow -
@ same simplified plain lock/faceplayer/Yes-No/heal sequence as Brightwell's
@ (see Wasteland_Brightwell_PokemonCenter/scripts.inc for why the shared
@ Common_EventScript_PkmnCenterNurse script is avoided here). Unlike
@ Brightwell, nothing here is "barely holding on" - this city's services
@ just work, which is itself the point of a corporate city.
Wasteland_Rustboro_PokemonCenter_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Wasteland_Rustboro_PokemonCenter_OnTransition
	.byte 0

Wasteland_Rustboro_PokemonCenter_OnTransition:
	setrespawn HEAL_LOCATION_WASTELAND_RUSTBORO
	end

Wasteland_Rustboro_PokemonCenter_EventScript_Nurse::
	lock
	faceplayer
	msgbox Wasteland_Rustboro_PokemonCenter_Text_WouldYouLikeToHeal, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Wasteland_Rustboro_PokemonCenter_EventScript_NoThanks
	message Wasteland_Rustboro_PokemonCenter_Text_OneMoment
	waitmessage
	special HealPlayerParty
	msgbox Wasteland_Rustboro_PokemonCenter_Text_AllSet, MSGBOX_DEFAULT
	release
	end

Wasteland_Rustboro_PokemonCenter_EventScript_NoThanks::
	msgbox Wasteland_Rustboro_PokemonCenter_Text_ComeAgain, MSGBOX_DEFAULT
	release
	end

Wasteland_Rustboro_PokemonCenter_Text_WouldYouLikeToHeal::
	.string "Welcome. Shall I take your POKéMON\n"
	.string "for evaluation and treatment?$"

Wasteland_Rustboro_PokemonCenter_Text_OneMoment::
	.string "One moment, please.$"

Wasteland_Rustboro_PokemonCenter_Text_AllSet::
	.string "All set. Your POKéMON are in\n"
	.string "excellent condition.$"

Wasteland_Rustboro_PokemonCenter_Text_ComeAgain::
	.string "Of course. Do come again.$"
