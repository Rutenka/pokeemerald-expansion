@ A real, whole, unmodified crop of vanilla RusturfTunnel's layout (General+
@ RusturfTunnel), reused purely for its tile art and its two real, working
@ door tiles - none of the vanilla map's own NPCs/scripts/state machine were
@ carried over (fresh, empty object_events/coord_events, per the same pattern
@ already used for Wasteland_EstateHouse = RustboroCity_House1). This map
@ replaces the old coord_event-on-open-ground exit between the garden and the
@ road (see CLAUDE.md) with a real tunnel between two real, tile-for-tile
@ vanilla cave-mouth doors - one matching the garden's own tileset (copied
@ from Route116), one matching the road's (copied from VerdanturfTown).
Wasteland_EstateTunnel_MapScripts::
	.byte 0
