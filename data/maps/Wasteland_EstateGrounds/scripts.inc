@ The garden, rebuilt as a genuine standalone place between the house and the
@ road (2026-09-12) - a real, whole, unmodified crop of vanilla Route104's
@ lake/garden/house area (General+Rustboro), used as a single self-contained
@ map. BOTH transitions are now real native doors, not scripted warps on
@ open ground - see the Sixteenth custom feature entry in CLAUDE.md for why
@ the previous coord_event-on-a-hedge-gap approach was replaced entirely.
@ warp_events[0] sits on this crop's own real Pretty Petal Flower Shop door
@ (local (5,8)) and targets Wasteland_EstateHouse's garden door directly.
@ warp_events[1] sits on a real cave-mouth door (local (10,17), tile-for-tile
@ copied from Route116's own real tunnel entrance, same General+Rustboro
@ tileset) and leads into Wasteland_EstateTunnel, which comes out the other
@ side into Wasteland_Road through its own matching real door. No coord_event
@ is needed for either transition anymore.
Wasteland_EstateGrounds_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Wasteland_EstateGrounds_OnFrame
	.byte 0

Wasteland_EstateGrounds_OnFrame:
	map_script_2 VAR_WASTELAND_ESTATE_GROUNDS_STATE, 0, Wasteland_EstateGrounds_EventScript_FixRenderGlitch
	.2byte 0

@ Real, reproducible bug, confirmed via a real headless frame-by-frame test
@ (not assumed, and not the same as the Safe Room's "corruption" - that one
@ turned out to be correct tile data at a bad size, this one is genuine
@ runtime corruption: a static per-tile render of this map's own map.bin
@ shows no glitch at all, so the map data itself is fine). On arrival, a
@ garbled noise patch reliably appears in the screen's top-left corner
@ roughly 50 frames after the map loads - with zero player input - and is
@ fully cleared by any single subsequent real player movement. Root cause
@ not fully understood even after a dedicated investigation (see the
@ Eleventh feature entry in CLAUDE.md - connection border-fill, tileset
@ mismatch, and several warp/fade variants were all ruled out as the sole
@ mechanism), but the fix doesn't need the root cause: force exactly the
@ kind of harmless movement already proven to clear it, automatically,
@ timed to land after the glitch's observed onset window (confirmed still
@ present at frame 59, absent at 47) so the player is never meant to
@ actually see it.
Wasteland_EstateGrounds_EventScript_FixRenderGlitch::
	setvar VAR_WASTELAND_ESTATE_GROUNDS_STATE, 1
	delay 75
	lockall
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	releaseall
	end

Wasteland_EstateGrounds_EventScript_Aftermath::
	setflag FLAG_SEEN_ESTATE_GROUNDS_AFTERMATH
	lockall
	msgbox Wasteland_EstateGrounds_Text_Aftermath, MSGBOX_DEFAULT
	releaseall
	end

Wasteland_EstateGrounds_Text_Aftermath::
	.string "The garden is wrong in a way that\n"
	.string "takes a moment to place.\p"
	.string "Trampled beds. The pond sits flat\n"
	.string "and still, choked with algae.\p"
	.string "No dogs bark. No footsteps but your\n"
	.string "own.\p"
	.string "Whatever happened here, it's already\n"
	.string "over.$"
