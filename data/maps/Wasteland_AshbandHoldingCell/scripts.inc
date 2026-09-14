@ Reuses vanilla MagmaHideout_2F_1R's real layout verbatim, one of three real
@ doors on the checkpoint floor that were left unwired until Viktor found the
@ resulting dead end during a live playtest (2026-09-13) - see CLAUDE.md.
@ Fires its one-shot arrival narration via MAP_SCRIPT_ON_FRAME_TABLE, the same
@ proven-safe pattern as Wasteland_SafeRoom's cutscene (a lockall/msgbox
@ sequence here doesn't depend on any specific landing/trigger tile, so it
@ carries none of the "coord_event on the wrong tile" risk class).
Wasteland_AshbandHoldingCell_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Wasteland_AshbandHoldingCell_OnFrame
	.byte 0

Wasteland_AshbandHoldingCell_OnFrame:
	map_script_2 VAR_WASTELAND_HOLDING_CELL_STATE, 0, Wasteland_AshbandHoldingCell_EventScript_Arrival
	.2byte 0

Wasteland_AshbandHoldingCell_EventScript_Arrival::
	setvar VAR_WASTELAND_HOLDING_CELL_STATE, 1
	lockall
	msgbox Wasteland_AshbandHoldingCell_Text_1, MSGBOX_DEFAULT
	closemessage
	msgbox Wasteland_AshbandHoldingCell_Text_2, MSGBOX_DEFAULT
	releaseall
	end

Wasteland_AshbandHoldingCell_Text_1::
	.string "The air is colder here, and it\n"
	.string "smells like rust.\p"
	.string "A cell door hangs open. Something's\n"
	.string "torn and left hanging on a nail -\l"
	.string "a coat. His coat.$"

Wasteland_AshbandHoldingCell_Text_2::
	.string "It's not much. But it means he was\n"
	.string "alive, at least this far in.$"
