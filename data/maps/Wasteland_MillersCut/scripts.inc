@ Vanilla Jagged Pass, reused wholesale (General+Lavaridge) - picked for the
@ name fit (a genuinely jagged, treacherous cut through rock) and because
@ reusing a whole real map sidesteps this project's entire history of
@ crop-and-stitch seam bugs. Its own real warp structure is reused as-is:
@ the real south door (Route112 in vanilla) now leads back to Brightwell's
@ own real, previously-unused Rusturf-Tunnel-style door at local (8,1) (an
@ exact byte-for-byte match with real VerdanturfTown data at that
@ coordinate - never wired up before now); the real mid-map cave-mouth
@ entrance (Magma Hideout in vanilla) now leads to Wasteland_AshbandCheckpoint.
@ The real north door (Mt. Chimney in vanilla) is deliberately left unwired -
@ see tools/validate_maps.py's own "door with no warp" warning for it, which
@ is correct here: it's the physical hook for continuing Miller's Cut later,
@ not a bug.
Wasteland_MillersCut_MapScripts::
	.byte 0

Wasteland_MillersCut_EventScript_Aftermath::
	setflag FLAG_SEEN_MILLERS_CUT_AFTERMATH
	lockall
	msgbox Wasteland_MillersCut_Text_Aftermath, MSGBOX_DEFAULT
	releaseall
	end

@ Second Ashband encounter, same sight-triggered ambush pattern as the Road's
@ scout (see Wasteland_Road/scripts.inc) - consistent characterization, not
@ a one-off.
Wasteland_MillersCut_EventScript_AshbandLookout::
	trainerbattle_single TRAINER_ASHBAND_LOOKOUT, Wasteland_MillersCut_Text_LookoutIntro, Wasteland_MillersCut_Text_LookoutDefeat, Wasteland_MillersCut_EventScript_LookoutFlees
	end

Wasteland_MillersCut_EventScript_LookoutFlees::
	setflag FLAG_DEFEATED_ASHBAND_LOOKOUT
	applymovement 1, Wasteland_MillersCut_Movement_LookoutFlees
	waitmovement 0
	removeobject 1
	end

Wasteland_MillersCut_Movement_LookoutFlees:
	walk_up
	walk_up
	step_end

Wasteland_MillersCut_Text_Aftermath::
	.string "The road narrows to bare rock here.\n"
	.string "Something cut this pass on purpose -\l"
	.string "the walls are too even for weather.\p"
	.string "Boot prints in the dust. Recent.\n"
	.string "Not yours.$"

Wasteland_MillersCut_Text_LookoutIntro::
	.string "Nobody comes up Miller's Cut by\n"
	.string "accident.$"

Wasteland_MillersCut_Text_LookoutDefeat::
	.string "Fine! Fine. I didn't see you.\n"
	.string "You didn't see me.$"
