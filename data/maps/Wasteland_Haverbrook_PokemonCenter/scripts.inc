@ The real, shared Pokemon Center interior + the engine's own healing flow -
@ same simplified plain lock/faceplayer/Yes-No/heal sequence proven at
@ Brightwell and Rustboro (see either for why the shared
@ Common_EventScript_PkmnCenterNurse script is avoided).
Wasteland_Haverbrook_PokemonCenter_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Wasteland_Haverbrook_PokemonCenter_OnTransition
	.byte 0

Wasteland_Haverbrook_PokemonCenter_OnTransition:
	setrespawn HEAL_LOCATION_WASTELAND_HAVERBROOK
	end

Wasteland_Haverbrook_PokemonCenter_EventScript_Nurse::
	lock
	faceplayer
	msgbox Wasteland_Haverbrook_PokemonCenter_Text_WouldYouLikeToHeal, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Wasteland_Haverbrook_PokemonCenter_EventScript_NoThanks
	message Wasteland_Haverbrook_PokemonCenter_Text_OneMoment
	waitmessage
	special HealPlayerParty
	msgbox Wasteland_Haverbrook_PokemonCenter_Text_AllSet, MSGBOX_DEFAULT
	release
	end

Wasteland_Haverbrook_PokemonCenter_EventScript_NoThanks::
	msgbox Wasteland_Haverbrook_PokemonCenter_Text_ComeAgain, MSGBOX_DEFAULT
	release
	end

Wasteland_Haverbrook_PokemonCenter_Text_WouldYouLikeToHeal::
	.string "You made it in one piece. Want me\n"
	.string "to patch your team up?$"

Wasteland_Haverbrook_PokemonCenter_Text_OneMoment::
	.string "Hold still, then.$"

Wasteland_Haverbrook_PokemonCenter_Text_AllSet::
	.string "Good as new. We look after our\n"
	.string "own out here.$"

Wasteland_Haverbrook_PokemonCenter_Text_ComeAgain::
	.string "Fair enough. Door's open when you\n"
	.string "change your mind.$"
