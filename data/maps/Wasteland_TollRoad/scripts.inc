Wasteland_TollRoad_MapScripts::
	.byte 0

Wasteland_TollRoad_EventScript_Kid::
	lock
	faceplayer
	msgbox Wasteland_TollRoad_Text_Kid, MSGBOX_DEFAULT
	release
	end

Wasteland_TollRoad_Text_Kid::
	.string "Wardens don't hurt the ones who\n"
	.string "pay. I never had anything to pay\l"
	.string "with, so I carry their bags. They\l"
	.string "say it's the same thing.$"

Wasteland_TollRoad_EventScript_Boy::
	lock
	faceplayer
	msgbox Wasteland_TollRoad_Text_Boy, MSGBOX_DEFAULT
	release
	end

Wasteland_TollRoad_Text_Boy::
	.string "My dad says never stand near the\n"
	.string "company trucks at night. He won't\l"
	.string "say why. He just says it.$"

Wasteland_TollRoad_EventScript_SignWest::
	msgbox Wasteland_TollRoad_Text_SignWest, MSGBOX_SIGN
	end

Wasteland_TollRoad_Text_SignWest::
	.string "HAVERBROOK, west.\p"
	.string "THE CROSSING, east. Toll road.\n"
	.string "Fees payable to any warden.\l"
	.string "Unpaid fees are filed as debt.$"

Wasteland_TollRoad_EventScript_SignEast::
	msgbox Wasteland_TollRoad_Text_SignEast, MSGBOX_SIGN
	end

Wasteland_TollRoad_Text_SignEast::
	.string "THE CROSSING, one hour on.\p"
	.string "A toll is a courtesy. Refusal is\n"
	.string "noted.$"

Wasteland_TollRoad_EventScript_Warden1::
	trainerbattle_single TRAINER_TOLL_WARDEN_1, Wasteland_TollRoad_Text_Warden1Intro, Wasteland_TollRoad_Text_Warden1Defeat
	msgbox Wasteland_TollRoad_Text_Warden1Post, MSGBOX_AUTOCLOSE
	end

Wasteland_TollRoad_Text_Warden1Intro::
	.string "You walked past the marker.\n"
	.string "That's a fee, a fine, and a form.\l"
	.string "Let's settle it the quick way.$"

Wasteland_TollRoad_Text_Warden1Defeat::
	.string "Fee waived. I'll have to write\n"
	.string "that down.$"

Wasteland_TollRoad_Text_Warden1Post::
	.string "Go on. I'll file this under\n"
	.string "Regrettable.$"

Wasteland_TollRoad_EventScript_Warden2::
	trainerbattle_single TRAINER_TOLL_WARDEN_2, Wasteland_TollRoad_Text_Warden2Intro, Wasteland_TollRoad_Text_Warden2Defeat
	msgbox Wasteland_TollRoad_Text_Warden2Post, MSGBOX_AUTOCLOSE
	end

Wasteland_TollRoad_Text_Warden2Intro::
	.string "Hold it. Manifest?$"

Wasteland_TollRoad_Text_Warden2Defeat::
	.string "That's irregular. I'll need a\n"
	.string "form for that.$"

Wasteland_TollRoad_Text_Warden2Post::
	.string "Take the road. The Crossing's\n"
	.string "ahead. Try not to leave a mess.$"

