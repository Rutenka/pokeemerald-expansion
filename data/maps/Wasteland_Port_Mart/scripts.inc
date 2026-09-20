@ Shared Mart interior. Stock is whatever the docks let through.
Wasteland_Port_Mart_MapScripts::
	.byte 0

Wasteland_Port_Mart_EventScript_Clerk::
	lock
	faceplayer
	message Wasteland_Port_Mart_Text_Welcome
	waitmessage
	pokemart Wasteland_Port_Mart_Pokemart
	msgbox Wasteland_Port_Mart_Text_Goodbye, MSGBOX_DEFAULT
	release
	end

	.align 2
Wasteland_Port_Mart_Pokemart:
	.2byte ITEM_POKE_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_HYPER_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_REVIVE
	.2byte ITEM_REPEL
	pokemartlistend

Wasteland_Port_Mart_Text_Welcome::
	.string "Port prices. The fee is included.\n"
	.string "So is the other fee. What'll it\l"
	.string "be?$"

Wasteland_Port_Mart_Text_Goodbye::
	.string "Receipt's in the bag. Don't lose\n"
	.string "it. They check.$"

