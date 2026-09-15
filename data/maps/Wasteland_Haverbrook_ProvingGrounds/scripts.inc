@ Reuses vanilla Route110_TrickHouseEntrance's real, small single-room
@ layout verbatim - deliberately modest in scale (not a Gym-sized gauntlet),
@ matching Haverbrook's own "no corporate polish" identity. Territory 3's
@ boss fight (CLAUDE.md's Thirty-first feature entry) - a respected local
@ protector, not a villain, the first "Pokemon partnership is good, not
@ just a weapon" beat after two "everyone's compromised" chapters.
Wasteland_Haverbrook_ProvingGrounds_MapScripts::
	.byte 0

Wasteland_Haverbrook_ProvingGrounds_EventScript_Garrick::
	trainerbattle_single TRAINER_HAVERBROOK_PROTECTOR, Wasteland_Haverbrook_ProvingGrounds_Text_GarrickIntro, Wasteland_Haverbrook_ProvingGrounds_Text_GarrickDefeat, Wasteland_Haverbrook_ProvingGrounds_EventScript_GarrickDefeated
	msgbox Wasteland_Haverbrook_ProvingGrounds_Text_GarrickPostBattle, MSGBOX_DEFAULT
	release
	end

Wasteland_Haverbrook_ProvingGrounds_EventScript_GarrickDefeated::
	setflag FLAG_DEFEATED_HAVERBROOK_PROTECTOR
	msgbox Wasteland_Haverbrook_ProvingGrounds_Text_GarrickCongrats, MSGBOX_DEFAULT
	release
	end

Wasteland_Haverbrook_ProvingGrounds_Text_GarrickIntro::
	.string "So you're the one who crossed the\n"
	.string "Cut. Rustboro's boy, or Rustboro's\l"
	.string "problem - either way, let's see\l"
	.string "what you've actually got.$"

Wasteland_Haverbrook_ProvingGrounds_Text_GarrickDefeat::
	.string "Hah! Fair enough.$"

Wasteland_Haverbrook_ProvingGrounds_Text_GarrickPostBattle::
	.string "Nobody's beaten me on my own floor\n"
	.string "in a long while.$"

Wasteland_Haverbrook_ProvingGrounds_Text_GarrickCongrats::
	.string "You didn't come here looking for a\n"
	.string "badge or a certificate. You came\l"
	.string "looking for your father.\p"
	.string "I don't know the man. But I know\n"
	.string "what it costs to walk through a\l"
	.string "warlord's road and a corporation's\l"
	.string "gate just to keep looking.\p"
	.string "Whatever's further out there,\n"
	.string "you've earned the right to find\l"
	.string "it. Good luck.$"
