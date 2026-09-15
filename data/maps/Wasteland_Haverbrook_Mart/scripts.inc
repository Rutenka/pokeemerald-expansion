@ The real, shared Mart interior (LAYOUT_MART) - a genuinely well-stocked
@ trading post, fitting for a settlement whose whole identity is trade.
Wasteland_Haverbrook_Mart_MapScripts::
	.byte 0

Wasteland_Haverbrook_Mart_EventScript_Clerk::
	lock
	faceplayer
	message Wasteland_Haverbrook_Mart_Text_HowMayIServeYou
	waitmessage
	pokemart Wasteland_Haverbrook_Mart_Pokemart
	msgbox Wasteland_Haverbrook_Mart_Text_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
Wasteland_Haverbrook_Mart_Pokemart:
	.2byte ITEM_POKE_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_POTION
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_REPEL
	pokemartlistend

Wasteland_Haverbrook_Mart_Text_HowMayIServeYou::
	.string "Trade's fair here. What do you\n"
	.string "need?$"

Wasteland_Haverbrook_Mart_Text_PleaseComeAgain::
	.string "Safe travels, whichever way you're\n"
	.string "headed.$"
