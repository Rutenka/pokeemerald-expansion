@ Pure connective route between the estate grounds and Brightwell - no NPCs,
@ no narration beat of its own (that lives in Wasteland_EstateGrounds, where
@ the story beat actually belongs).
@
@ The Brightwell side (right) is a real map connection (see map.json) - both
@ maps share the same secondary tileset (Mauville), confirmed clean via a
@ real headless screenshot.
@
@ The estate grounds side is now a real cave-mouth door (local (17,6),
@ tile-for-tile copied from VerdanturfTown's own real RusturfTunnel entrance,
@ same General+Mauville tileset) leading into Wasteland_EstateTunnel, which
@ comes out the other side into Wasteland_EstateGrounds through its own
@ matching real door. See the Sixteenth custom feature entry in CLAUDE.md for
@ why the previous coord_event-on-open-ground exit was replaced entirely.
Wasteland_Road_MapScripts::
	.byte 0
