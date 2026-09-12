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

@ First trainer battle in the game - an Ashband scout (the raider faction
@ that hit the estate and took Dad, per Rourke's dialogue in Brightwell)
@ posted near the tall grass to watch this stretch of road. Sight-triggered
@ (TRAINER_TYPE_NORMAL in map.json), not a walk-up-and-press-A NPC, since a
@ raider ambushing the player fits the story better than a polite duel
@ request - and it's the same "won't announce themselves before they do"
@ warning Rourke gives moments later in Brightwell, played out firsthand
@ before the player ever hears it named. Losing sends them fleeing back into
@ the grass for good (FLAG_DEFEATED_ASHBAND_SCOUT both ends the encounter
@ and hides the object permanently, same pattern used for Dad in the Safe
@ Room).
Wasteland_Road_EventScript_AshbandScout::
	trainerbattle_single TRAINER_ASHBAND_SCOUT, Wasteland_Road_Text_ScoutIntro, Wasteland_Road_Text_ScoutDefeat, Wasteland_Road_EventScript_ScoutFlees
	end

@ Local ID 1 - the scout is this map's only object event (matches the Safe
@ Room's own convention of referencing a map's sole NPC by plain numeric
@ local id rather than a named LOCALID_ constant).
Wasteland_Road_EventScript_ScoutFlees::
	setflag FLAG_DEFEATED_ASHBAND_SCOUT
	applymovement 1, Wasteland_Road_Movement_ScoutFlees
	waitmovement 0
	removeobject 1
	end

Wasteland_Road_Movement_ScoutFlees:
	walk_down
	walk_down
	step_end

Wasteland_Road_Text_ScoutIntro::
	.string "You're the one from the estate.\n"
	.string "Can't have you running your mouth\l"
	.string "in town.$"

Wasteland_Road_Text_ScoutDefeat::
	.string "This isn't - forget it. Forget I\n"
	.string "was even here.$"
