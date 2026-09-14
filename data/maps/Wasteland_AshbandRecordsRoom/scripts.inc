@ Reuses vanilla MagmaHideout_2F_3R's real layout verbatim - see
@ Wasteland_AshbandHoldingCell/scripts.inc for why MAP_SCRIPT_ON_FRAME_TABLE
@ is used for this one-shot arrival narration. This is the "hook" room -
@ confirmed via Viktor's own decision (2026-09-13) that the Ashband are
@ supplied directly by the same corporation the player already suspects.
Wasteland_AshbandRecordsRoom_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Wasteland_AshbandRecordsRoom_OnFrame
	.byte 0

Wasteland_AshbandRecordsRoom_OnFrame:
	map_script_2 VAR_WASTELAND_RECORDS_ROOM_STATE, 0, Wasteland_AshbandRecordsRoom_EventScript_Arrival
	.2byte 0

Wasteland_AshbandRecordsRoom_EventScript_Arrival::
	setvar VAR_WASTELAND_RECORDS_ROOM_STATE, 1
	lockall
	msgbox Wasteland_AshbandRecordsRoom_Text_1, MSGBOX_DEFAULT
	closemessage
	msgbox Wasteland_AshbandRecordsRoom_Text_2, MSGBOX_DEFAULT
	closemessage
	msgbox Wasteland_AshbandRecordsRoom_Text_3, MSGBOX_DEFAULT
	releaseall
	end

Wasteland_AshbandRecordsRoom_Text_1::
	.string "A ledger, left open on a crate lid.\n"
	.string "Deliveries. Dates. Quantities.$"

Wasteland_AshbandRecordsRoom_Text_2::
	.string "At the bottom of every page, the\n"
	.string "same signature line:\l"
	.string "DEVON CORPORATION - LOGISTICS.$"

Wasteland_AshbandRecordsRoom_Text_3::
	.string "The Ashband aren't just surviving\n"
	.string "out here.\p"
	.string "Someone's been feeding them.$"
