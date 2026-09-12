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
	.byte 0

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
