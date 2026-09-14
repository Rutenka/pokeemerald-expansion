@ Reuses vanilla MagmaHideout_2F_2R's real layout verbatim - see
@ Wasteland_AshbandHoldingCell/scripts.inc for why MAP_SCRIPT_ON_FRAME_TABLE
@ is used for this one-shot arrival narration.
Wasteland_AshbandSupplyCache_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Wasteland_AshbandSupplyCache_OnFrame
	.byte 0

Wasteland_AshbandSupplyCache_OnFrame:
	map_script_2 VAR_WASTELAND_SUPPLY_CACHE_STATE, 0, Wasteland_AshbandSupplyCache_EventScript_Arrival
	.2byte 0

Wasteland_AshbandSupplyCache_EventScript_Arrival::
	setvar VAR_WASTELAND_SUPPLY_CACHE_STATE, 1
	lockall
	msgbox Wasteland_AshbandSupplyCache_Text_1, MSGBOX_DEFAULT
	closemessage
	msgbox Wasteland_AshbandSupplyCache_Text_2, MSGBOX_DEFAULT
	releaseall
	end

Wasteland_AshbandSupplyCache_Text_1::
	.string "Crates, stacked floor to ceiling.\n"
	.string "Most are unmarked.\p"
	.string "A few aren't.$"

Wasteland_AshbandSupplyCache_Text_2::
	.string "Stamped on the side of each one: a\n"
	.string "company crest that has no business\l"
	.string "being out here.$"
