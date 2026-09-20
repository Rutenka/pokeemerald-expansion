Wasteland_Port_Hall_MapScripts::
	.byte 0

Wasteland_Port_Hall_EventScript_Tally::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_HARBORMASTER, Wasteland_Port_Hall_EventScript_TallyAfter
	specialvar VAR_RESULT, CalculatePlayerPartyCount
	goto_if_ne VAR_RESULT, 3, Wasteland_Port_Hall_EventScript_TallyWrongPartySize
	trainerbattle_single TRAINER_HARBORMASTER, Wasteland_Port_Hall_Text_TallyIntro, Wasteland_Port_Hall_Text_TallyDefeat, Wasteland_Port_Hall_EventScript_TallyDefeated, NO_MUSIC
	msgbox Wasteland_Port_Hall_Text_TallyAfter, MSGBOX_DEFAULT
	release
	end

Wasteland_Port_Hall_EventScript_TallyWrongPartySize::
	msgbox Wasteland_Port_Hall_Text_TallyWrongPartySize, MSGBOX_DEFAULT
	release
	end

Wasteland_Port_Hall_EventScript_TallyDefeated::
	setflag FLAG_DEFEATED_HARBORMASTER
	msgbox Wasteland_Port_Hall_Text_TallyReveal, MSGBOX_DEFAULT
	release
	end

Wasteland_Port_Hall_EventScript_TallyAfter::
	msgbox Wasteland_Port_Hall_Text_TallyAfter, MSGBOX_DEFAULT
	release
	end

Wasteland_Port_Hall_Text_TallyWrongPartySize::
	.string "Three. Every contest in my hall\n"
	.string "is three against three. It's on\l"
	.string "the form. Sort your team, then\l"
	.string "come back.$"

Wasteland_Port_Hall_Text_TallyIntro::
	.string "You registered as Smith. Everyone\n"
	.string "does. It's a tradition, and I\l"
	.string "keep the register anyway.\p"
	.string "Twelve hundred names on it. Every\n"
	.string "one dated, every one last seen.\l"
	.string "You want to leave through my\l"
	.string "port? Then earn your line in it.$"

Wasteland_Port_Hall_Text_TallyDefeat::
	.string "Entry filed. You fight like\n"
	.string "someone who was told the world\l"
	.string "was kinder than it is.$"

Wasteland_Port_Hall_Text_TallyReveal::
	.string "That Houndour. I've seen that dog\n"
	.string "before, on the lead of a man who\l"
	.string "signed the last page of my\l"
	.string "ledger. The one behind the\l"
	.string "switch.\p"
	.string "You are his. Don't bother denying\n"
	.string "it. You hold the leash the same\l"
	.string "way.\p"
	.string "You were right to hide it. The\n"
	.string "name was never the problem. What\l"
	.string "he did to my people was.\p"
	.string "Fifty-one taken in the last year.\n"
	.string "People, and their Pokemon. They\l"
	.string "left on company trucks and never\l"
	.string "came back. I don't know where.\l"
	.string "All I have are rumors, and that's\l"
	.string "what a register is for.\p"
	.string "It keeps rumors from turning into\n"
	.string "forgetting.\p"
	.string "The supply boats leave for the\n"
	.string "overgrown ruins down the coast.\l"
	.string "Whoever arms the Ashband doesn't\l"
	.string "stop at my dock. Go and look.$"

Wasteland_Port_Hall_Text_TallyAfter::
	.string "The register's open. Every name\n"
	.string "in it is one somebody asked me to\l"
	.string "remember. Go and find yours.$"

