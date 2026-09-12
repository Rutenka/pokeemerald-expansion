@ The whole opening scene is a forced cutscene, not something the player walks up
@ to and triggers: it fires the instant the map is standing (MAP_SCRIPT_ON_FRAME_TABLE,
@ the same mechanism vanilla uses for e.g. the Littleroot truck-unloading scene),
@ with the player lockall'd the entire time. MAP_SCRIPT_ON_LOAD/ON_TRANSITION were
@ tried first and both hang here - RunScriptImmediately() executes those in one
@ blocking loop with no per-frame yield, so lock/msgbox/applymovement+waitmovement
@ (which all need to be polled once per game frame to ever report "done") spin
@ forever. ON_FRAME_TABLE scripts run through the normal per-frame script context
@ instead, so they behave exactly like any other script. VAR_WASTELAND_SAFE_ROOM_STATE
@ is what makes it fire exactly once: it's 0 on a fresh save (vars default to 0), the
@ table below matches on 0, and the cutscene's own first action sets it to 1 so the
@ table stops matching from the next frame on.
Wasteland_SafeRoom_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Wasteland_SafeRoom_OnFrame
	.byte 0

Wasteland_SafeRoom_OnFrame:
	map_script_2 VAR_WASTELAND_SAFE_ROOM_STATE, 0, Wasteland_SafeRoom_EventScript_OpeningCutscene
	.2byte 0

Wasteland_SafeRoom_EventScript_OpeningCutscene::
	setvar VAR_WASTELAND_SAFE_ROOM_STATE, 1
	lockall
	turnobject LOCALID_PLAYER, DIR_NORTH
	msgbox Wasteland_SafeRoom_Text_DadUrgent1, MSGBOX_DEFAULT
	givemon SPECIES_HOUNDOUR_ALDER, 5
	goto_if_eq VAR_RESULT, 0, Wasteland_SafeRoom_EventScript_GaveStarterParty
	goto_if_eq VAR_RESULT, 1, Wasteland_SafeRoom_EventScript_GaveStarterPC
	goto_if_eq VAR_RESULT, 2, Wasteland_SafeRoom_EventScript_NoRoomForStarter
	end

Wasteland_SafeRoom_EventScript_GaveStarterParty::
	setflag FLAG_SYS_POKEMON_GET
	goto Wasteland_SafeRoom_EventScript_DadLeaves
	end

Wasteland_SafeRoom_EventScript_GaveStarterPC::
	setflag FLAG_SYS_POKEMON_GET
	msgbox Wasteland_SafeRoom_Text_DadGiveStarterSentToPC, MSGBOX_DEFAULT
	goto Wasteland_SafeRoom_EventScript_DadLeaves
	end

@ Shouldn't come up this early (party+PC both full on a fresh save), but handled
@ for completeness. Not using the shared Common_EventScript_NoMoreRoomForPokemon
@ here since it ends on a plain `release`, not `releaseall` - would leave things
@ half-locked after our `lockall`.
Wasteland_SafeRoom_EventScript_NoRoomForStarter::
	msgbox gText_NoMoreRoomForPokemon, MSGBOX_DEFAULT
	goto Wasteland_SafeRoom_EventScript_DadLeaves
	end

Wasteland_SafeRoom_EventScript_DadLeaves::
	setflag FLAG_RECEIVED_WASTELAND_STARTER
	msgbox Wasteland_SafeRoom_Text_DadUrgent2, MSGBOX_DEFAULT
	closemessage
	applymovement 1, Wasteland_SafeRoom_Movement_DadExits
	waitmovement 0
	playse SE_DOOR
	removeobject 1
	delay 30
	msgbox Wasteland_SafeRoom_Text_Aftermath1, MSGBOX_DEFAULT
	closemessage
	playse SE_WALL_HIT
	msgbox Wasteland_SafeRoom_Text_Aftermath2, MSGBOX_DEFAULT
	closemessage
	playse SE_M_STRENGTH
	msgbox Wasteland_SafeRoom_Text_Aftermath3, MSGBOX_DEFAULT
	closemessage
	playse SE_ICE_BREAK
	msgbox Wasteland_SafeRoom_Text_Aftermath4, MSGBOX_DEFAULT
	closemessage
	msgbox Wasteland_SafeRoom_Text_Aftermath5, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	delay 90
	fadescreen FADE_FROM_BLACK
	msgbox Wasteland_SafeRoom_Text_Aftermath6, MSGBOX_DEFAULT
	closemessage
	msgbox Wasteland_SafeRoom_Text_Aftermath7, MSGBOX_DEFAULT
	releaseall
	end

@ Dad now stands at (2,2), player at (2,3) (see map.json - warp 1, a landing-
@ only spot facing him), door at (2,5)/(3,5), so a straight 3-tile walk south
@ takes him right out through it.
Wasteland_SafeRoom_Movement_DadExits:
	walk_down
	walk_down
	walk_down
	step_end

@ Dad is removed from the map partway through the opening cutscene above and his
@ object event's "flag" (FLAG_RECEIVED_WASTELAND_STARTER) keeps him hidden on any
@ later visit, so this normally can't be triggered by walking up and pressing A -
@ the player never has control while he's still present. Kept only as a defensive
@ fallback (e.g. debug tools clearing his hide flag), same as before the rewrite.
Wasteland_SafeRoom_EventScript_DadFallback::
	lock
	faceplayer
	msgbox Wasteland_SafeRoom_Text_DadAfter, MSGBOX_DEFAULT
	release
	end

Wasteland_SafeRoom_Text_DadUrgent1::
	.string "DAD: Stay here - I can't lose you\n"
	.string "the same way I lost your mother.\p"
	.string "DAD: Houndour, with her. Now.$"

Wasteland_SafeRoom_Text_DadUrgent2::
	.string "DAD: Whatever you hear - you do not\n"
	.string "open this door. Not for anyone.\l"
	.string "Not until I come back for you.$"

Wasteland_SafeRoom_Text_DadGiveStarterSentToPC::
	.string "There was no room in your party, so\n"
	.string "HOUNDOUR was sent to a Box at home.$"

Wasteland_SafeRoom_Text_DadAfter::
	.string "DAD: Stay quiet. Just a little\n"
	.string "longer.$"

Wasteland_SafeRoom_Text_Aftermath1::
	.string "A door slams, somewhere below.$"

Wasteland_SafeRoom_Text_Aftermath2::
	.string "Shouting. Boots on a hard floor.$"

Wasteland_SafeRoom_Text_Aftermath3::
	.string "A scream, cut short.$"

Wasteland_SafeRoom_Text_Aftermath4::
	.string "Then nothing.$"

Wasteland_SafeRoom_Text_Aftermath5::
	.string "The quiet stretches on.$"

Wasteland_SafeRoom_Text_Aftermath6::
	.string "DAD doesn't come back.$"

Wasteland_SafeRoom_Text_Aftermath7::
	.string "Waiting any longer won't change that.$"
