Wasteland_Rustboro_Flat2_MapScripts::
	.byte 0

@ Opened 2026-09-15. Reuses real vanilla RustboroCity_Flat2_1F verbatim.
@ Kept the real vanilla flavor line ("Devon Corp's workers live here") as
@ the building's own framing, then built on it - a retired Devon employee
@ who still keeps old supplies out of habit, giving the player a genuinely
@ useful item as thanks for checking in on her.
Wasteland_Rustboro_Flat2_EventScript_OldWoman::
	lock
	faceplayer
	goto_if_set FLAG_WASTELAND_RUSTBORO_FLAT2_GAVE_ITEM, Wasteland_Rustboro_Flat2_EventScript_OldWomanAfter
	msgbox Wasteland_Rustboro_Flat2_Text_OldWoman, MSGBOX_DEFAULT
	giveitem ITEM_FULL_HEAL
	goto_if_eq VAR_RESULT, 0, Common_EventScript_ShowBagIsFull
	setflag FLAG_WASTELAND_RUSTBORO_FLAT2_GAVE_ITEM
	release
	end

Wasteland_Rustboro_Flat2_EventScript_OldWomanAfter::
	msgbox Wasteland_Rustboro_Flat2_Text_OldWomanAfter, MSGBOX_DEFAULT
	release
	end

Wasteland_Rustboro_Flat2_EventScript_Skitty::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_SKITTY, CRY_MODE_NORMAL
	msgbox Wasteland_Rustboro_Flat2_Text_Skitty, MSGBOX_DEFAULT
	waitmoncry
	release
	end

Wasteland_Rustboro_Flat2_Text_OldWoman::
	.string "DEVON CORPORATION's workers live in\n"
	.string "this building. My husband was one\l"
	.string "of them, thirty years.\p"
	.string "Retired before all this. Still\n"
	.string "keeps supplies around out of habit,\l"
	.string "though.\p"
	.string "Here - he won't miss one.$"

Wasteland_Rustboro_Flat2_Text_OldWomanAfter::
	.string "Old habits. You'd be surprised what\n"
	.string "people hang onto.$"

Wasteland_Rustboro_Flat2_Text_Skitty::
	.string "SKITTY: Nya!$"
