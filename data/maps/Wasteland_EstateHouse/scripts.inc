@ Pure transition space between the safe room and the estate grounds - no
@ NPCs, no narration beat happens here (the story doesn't call for one), just
@ a believable "bigger house" the player passes through. Layout is the real
@ vanilla RustboroCity_House1 map, with one patch: the placeholder TV/dresser
@ against the north wall was replaced with a real stairwell-alcove tile
@ arrangement copied verbatim from RustboroCity_Flat1_1F (same Building +
@ GenericBuilding tileset pair), and the safe-room warp moved onto it - so
@ leaving the safe room now visibly emerges from a stairwell in the wall
@ instead of appearing in the middle of open floor. See CLAUDE.md's
@ world-building checklist for why a real tile arrangement was copied in
@ rather than hand-picked from the tile sheet.
Wasteland_EstateHouse_MapScripts::
	.byte 0

@ The player arrives here (from the safe room's stairwell) still facing
@ north/up, the direction they were walking when they entered the door
@ below - turn them south so they're facing into the room, away from the
@ wall, instead of facing back into the stairwell they just came out of.
Wasteland_EstateHouse_EventScript_FaceEastOnArrival::
	turnobject LOCALID_PLAYER, DIR_SOUTH
	end
