Wasteland_Brightwell_MapScripts::
	.byte 0

Wasteland_Brightwell_EventScript_Aftermath::
	setflag FLAG_SEEN_BRIGHTWELL_AFTERMATH
	lockall
	msgbox Wasteland_Brightwell_Text_Aftermath, MSGBOX_DEFAULT
	releaseall
	end

Wasteland_Brightwell_EventScript_Survivor::
	lock
	faceplayer
	msgbox Wasteland_Brightwell_Text_Survivor, MSGBOX_DEFAULT
	release
	end

Wasteland_Brightwell_EventScript_PropagandaSign::
	msgbox Wasteland_Brightwell_Text_PropagandaSign, MSGBOX_SIGN
	end

Wasteland_Brightwell_EventScript_Witness::
	lock
	faceplayer
	msgbox Wasteland_Brightwell_Text_Witness, MSGBOX_DEFAULT
	release
	end

Wasteland_Brightwell_EventScript_Rourke::
	lock
	faceplayer
	msgbox Wasteland_Brightwell_Text_Rourke, MSGBOX_DEFAULT
	release
	end

Wasteland_Brightwell_EventScript_Kid::
	lock
	faceplayer
	msgbox Wasteland_Brightwell_Text_Kid, MSGBOX_DEFAULT
	release
	end

Wasteland_Brightwell_Text_Aftermath::
	.string "The checkpoint gate is bent outward,\n"
	.string "not in.\p"
	.string "Shop windows dark. Doors hanging\n"
	.string "open. Something's burned, recently.\p"
	.string "Nobody's called out a warning.\n"
	.string "Nobody's called out anything.$"

Wasteland_Brightwell_Text_Survivor::
	.string "…\p"
	.string "They told us the company kept us\n"
	.string "safe. That's what the checkpoints\l"
	.string "were for.\p"
	.string "Rebels came through two nights ago.\n"
	.string "Took records, hardware - not just\l"
	.string "food, not just guns.\p"
	.string "Went straight for the company office.\n"
	.string "Like they already knew where to\l"
	.string "look.\p"
	.string "If you're heading further in… watch\n"
	.string "yourself. Whatever they wanted,\l"
	.string "they got it.$"

Wasteland_Brightwell_Text_PropagandaSign::
	.string "A company placard, half torn from\n"
	.string "its post.\p"
	.string "“YOUR SAFETY IS OUR TOP PRIORITY.”\p"
	.string "(Priority subject to quarterly review\n"
	.string "and available checkpoint staffing.)$"

Wasteland_Brightwell_Text_Witness::
	.string "I saw them drag someone out through\n"
	.string "the checkpoint. Hands bound.\p"
	.string "Didn't get a good look at his face -\n"
	.string "they had him between two of them,\l"
	.string "moving fast.\p"
	.string "Whoever he was, he was alive when\n"
	.string "they took him. That's more than most\l"
	.string "folks here can say for their own.$"

Wasteland_Brightwell_Text_Rourke::
	.string "You're the one from the estate.\n"
	.string "Word travels fast when there's\l"
	.string "nothing left to do but talk.\p"
	.string "Your father, is it. If the Ashband\n"
	.string "took him alive, they didn't kill him\l"
	.string "for a reason.\p"
	.string "They took him toward Miller's Cut -\n"
	.string "that's their road, has been for\l"
	.string "years. Nobody friendly goes that way\n"
	.string "anymore.\p"
	.string "The Ashband aren't soldiers, and\n"
	.string "they aren't heroes, whatever story\l"
	.string "gets told about them out east.\p"
	.string "They're raiders. Lawless. They've\n"
	.string "burned towns smaller than this one\l"
	.string "for less than what happened here.\p"
	.string "If you're set on following that road,\n"
	.string "don't do it stupid. Watch every tree\l"
	.string "line. They won't announce themselves\n"
	.string "before they do.$"

Wasteland_Brightwell_Text_Kid::
	.string "…\p"
	.string "Everybody just left. Nobody said\n"
	.string "where.\p"
	.string "I'm just waiting by the well until\n"
	.string "someone comes back for me.$"
