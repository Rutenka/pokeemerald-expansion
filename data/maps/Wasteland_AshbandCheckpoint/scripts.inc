@ Vanilla Magma Hideout 1F, reused wholesale (General+Lavaridge, the same
@ real tileset pair as Wasteland_MillersCut, since they're real vanilla
@ neighbors) - a fortified cave-bunker interior, which is exactly what a
@ raider checkpoint operating out of rough terrain plausibly would be, with
@ zero new architecture invented. Only the real entrance corridor and one
@ real chamber near it are used - the rest of this large cave is left
@ unmodified but unused, same as any other whole-map reuse in this project.
Wasteland_AshbandCheckpoint_MapScripts::
	.byte 0

@ Same sight-triggered ambush pattern as every other Ashband grunt so far.
Wasteland_AshbandCheckpoint_EventScript_Grunt::
	trainerbattle_single TRAINER_ASHBAND_CHECKPOINT_GRUNT, Wasteland_AshbandCheckpoint_Text_GruntIntro, Wasteland_AshbandCheckpoint_Text_GruntDefeat, Wasteland_AshbandCheckpoint_EventScript_GruntFlees
	end

Wasteland_AshbandCheckpoint_EventScript_GruntFlees::
	setflag FLAG_DEFEATED_ASHBAND_CHECKPOINT_GRUNT
	applymovement 1, Wasteland_AshbandCheckpoint_Movement_GruntFlees
	waitmovement 0
	removeobject 1
	end

Wasteland_AshbandCheckpoint_Movement_GruntFlees:
	walk_down
	walk_down
	step_end

@ The checkpoint boss - a face-to-face confrontation rather than another
@ ambush, since by this point the player has walked in on her directly, not
@ been caught off guard. Losing hides her for good via the object's own
@ "flag" field (FLAG_DEFEATED_ASHBAND_ENFORCER, set right after the battle) -
@ that same flag also unlocks the mother's post-rescue dialogue below.
Wasteland_AshbandCheckpoint_EventScript_Enforcer::
	trainerbattle_single TRAINER_ASHBAND_ENFORCER, Wasteland_AshbandCheckpoint_Text_EnforcerIntro, Wasteland_AshbandCheckpoint_Text_EnforcerDefeat, Wasteland_AshbandCheckpoint_EventScript_EnforcerBeaten
	end

Wasteland_AshbandCheckpoint_EventScript_EnforcerBeaten::
	setflag FLAG_DEFEATED_ASHBAND_ENFORCER
	release
	end

@ Not a willing Ashband member - coerced into keeping the checkpoint's
@ systems running. Two-state dialogue: scared/warning before the enforcer is
@ dealt with, grateful afterward. Deliberately left in place afterward
@ rather than scripted to walk home - the Brightwell Kid thread stays open
@ for a future pass, not resolved here.
Wasteland_AshbandCheckpoint_EventScript_Mother::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_ASHBAND_ENFORCER, Wasteland_AshbandCheckpoint_EventScript_MotherAfter
	msgbox Wasteland_AshbandCheckpoint_Text_MotherBefore, MSGBOX_DEFAULT
	release
	end

Wasteland_AshbandCheckpoint_EventScript_MotherAfter::
	msgbox Wasteland_AshbandCheckpoint_Text_MotherAfter, MSGBOX_DEFAULT
	release
	end

Wasteland_AshbandCheckpoint_Text_GruntIntro::
	.string "Nobody gets past the checkpoint\n"
	.string "without the Enforcer's say-so.$"

Wasteland_AshbandCheckpoint_Text_GruntDefeat::
	.string "You'll regret this. She's back\n"
	.string "there - go on, then.$"

Wasteland_AshbandCheckpoint_Text_EnforcerIntro::
	.string "So you're the one who's been\n"
	.string "making a mess of my checkpoint.\p"
	.string "I run this stretch of the Cut. You\n"
	.string "don't walk through it without me\l"
	.string "saying so.$"

Wasteland_AshbandCheckpoint_Text_EnforcerDefeat::
	.string "…Fine. Take the road. It won't\n"
	.string "get you your father back any\l"
	.string "faster.$"

Wasteland_AshbandCheckpoint_Text_MotherBefore::
	.string "Please - just go. If she sees you\n"
	.string "talking to me, it'll go worse for\l"
	.string "both of us.\p"
	.string "I keep the lights on and the water\n"
	.string "running here. That's all. That's\l"
	.string "the only reason I'm still breathing.$"

Wasteland_AshbandCheckpoint_Text_MotherAfter::
	.string "It's really over? She's not coming\n"
	.string "back down here?\p"
	.string "I have a boy in Brightwell. He's\n"
	.string "probably given up waiting by now.\p"
	.string "Thank you. I don't - thank you.$"
