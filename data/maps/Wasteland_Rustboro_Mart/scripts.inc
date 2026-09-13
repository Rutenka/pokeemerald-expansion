@ The real, shared Mart interior (LAYOUT_MART) - unlike Brightwell's raided
@ mart, this one is fully stocked and staffed, matching the design brief's
@ "corporate cities survived... run genuinely functional societies" point.
Wasteland_Rustboro_Mart_MapScripts::
	.byte 0

Wasteland_Rustboro_Mart_EventScript_Clerk::
	lock
	faceplayer
	message Wasteland_Rustboro_Mart_Text_HowMayIServeYou
	waitmessage
	pokemart Wasteland_Rustboro_Mart_Pokemart
	msgbox Wasteland_Rustboro_Mart_Text_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
Wasteland_Rustboro_Mart_Pokemart:
	.2byte ITEM_POKE_BALL
	.2byte ITEM_POTION
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_REPEL
	pokemartlistend

Wasteland_Rustboro_Mart_Text_HowMayIServeYou::
	.string "Welcome. How can I help you today?$"

Wasteland_Rustboro_Mart_Text_PleaseComeAgain::
	.string "Thank you for your business.$"
