@ Reuses the real, shared Pokemon Center interior (LAYOUT_POKEMON_CENTER_1F,
@ same layout every vanilla town's center uses) and the engine's own shared
@ healing script (Common_EventScript_PkmnCenterNurse) - the machine genuinely
@ heals the player's party, same as any real Pokemon Center. Per Viktor's
@ decision (2026-09-12): this one still works, unlike the mart next door -
@ someone stayed and kept it running.
Wasteland_Brightwell_PokemonCenter_MapScripts::
	.byte 0

@ Real bug history: this originally called the engine's shared
@ Common_EventScript_PkmnCenterNurse (data/scripts/pkmn_center_nurse.inc), which
@ is what every vanilla Pokemon Center uses. That fixed an earlier double-lock
@ bug, but a *worse* bug remained: after healing, the player was left
@ completely frozen - not just a graphical leftover, confirmed by testing that
@ even the Start menu wouldn't open afterward, meaning a script was genuinely
@ stuck, not just a stale window. The shared script's healing path
@ (EventScript_PkmnCenterNurse_TakeAndHealPkmn) calls `applymovement
@ VAR_0x800B, Movement_PkmnCenterNurse_Turn` then `waitmovement 0` to turn the
@ nurse around for the animation, then a field effect for the ball-glow visual -
@ the working theory is this hangs specifically on this map (confirmed NOT
@ hanging on a real, untouched vanilla Pokemon Center given the identical test),
@ though the exact reason wasn't pinned down before time ran out on that
@ investigation. Rather than keep guessing at a script this project doesn't
@ own, this version skips the shared script's fancy movement/animation entirely
@ and heals directly and plainly - less flourish, but nothing left to hang on.
Wasteland_Brightwell_PokemonCenter_EventScript_Nurse::
	lock
	faceplayer
	msgbox Wasteland_Brightwell_PokemonCenter_Text_WouldYouLikeToHeal, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Wasteland_Brightwell_PokemonCenter_EventScript_NoThanks
	message Wasteland_Brightwell_PokemonCenter_Text_IllTakeThem
	waitmessage
	special HealPlayerParty
	msgbox Wasteland_Brightwell_PokemonCenter_Text_AllBetter, MSGBOX_DEFAULT
	release
	end

Wasteland_Brightwell_PokemonCenter_EventScript_NoThanks::
	msgbox Wasteland_Brightwell_PokemonCenter_Text_Okay, MSGBOX_DEFAULT
	release
	end

Wasteland_Brightwell_PokemonCenter_Text_WouldYouLikeToHeal::
	.string "Want me to take a look at your\n"
	.string "POKéMON?$"

Wasteland_Brightwell_PokemonCenter_Text_IllTakeThem::
	.string "Give me a moment.$"

Wasteland_Brightwell_PokemonCenter_Text_AllBetter::
	.string "There you go - good as new.$"

Wasteland_Brightwell_PokemonCenter_Text_Okay::
	.string "Suit yourself.$"
