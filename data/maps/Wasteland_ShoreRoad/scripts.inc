Wasteland_ShoreRoad_MapScripts::
	.byte 0

Wasteland_ShoreRoad_EventScript_Man::
	lock
	faceplayer
	msgbox Wasteland_ShoreRoad_Text_Man, MSGBOX_DEFAULT
	release
	end

Wasteland_ShoreRoad_Text_Man::
	.string "The trucks stop at the old pump\n"
	.string "house past the bend. Nobody sees\l"
	.string "them unload. Nobody asks.$"

Wasteland_ShoreRoad_EventScript_Boy::
	lock
	faceplayer
	msgbox Wasteland_ShoreRoad_Text_Boy, MSGBOX_DEFAULT
	release
	end

Wasteland_ShoreRoad_Text_Boy::
	.string "The wardens count everything.\n"
	.string "Steps. Coughs. I heard they count\l"
	.string "the missing too.$"

Wasteland_ShoreRoad_EventScript_Sign::
	msgbox Wasteland_ShoreRoad_Text_Sign, MSGBOX_SIGN
	end

Wasteland_ShoreRoad_Text_Sign::
	.string "SHORE ROAD. Harbor road ahead.\p"
	.string "Wardens on duty. Report\n"
	.string "irregularities to any warden.\l"
	.string "They are not sympathetic.$"

Wasteland_ShoreRoad_EventScript_FerrySign::
	msgbox Wasteland_ShoreRoad_Text_FerrySign, MSGBOX_SIGN
	end

Wasteland_ShoreRoad_Text_FerrySign::
	.string "SHORE FERRY.\p"
	.string "Runs when the ferryman feels like\n"
	.string "it. Toll: one signature. Unsigned\l"
	.string "crossings are filed as swimming.$"

Wasteland_ShoreRoad_EventScript_FerryWest::
	lock
	faceplayer
	msgbox Wasteland_ShoreRoad_Text_FerryWestAsk, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Wasteland_ShoreRoad_EventScript_FerryWestNo
	msgbox Wasteland_ShoreRoad_Text_FerryWestGo, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_PLAYER, DIR_WEST
	playse SE_SHIP
	fadescreen FADE_TO_BLACK
	delay 90
	warpsilent MAP_WASTELAND_SHORE_ROAD, 50, 10
	waitstate
	end

Wasteland_ShoreRoad_EventScript_FerryWestNo::
	msgbox Wasteland_ShoreRoad_Text_FerryNo, MSGBOX_DEFAULT
	release
	end

Wasteland_ShoreRoad_Text_FerryWestAsk::
	.string "Ferry to the east shore. Toll's\n"
	.string "one signature. You'll want to\l"
	.string "read the form. Nobody does.\p"
	.string "Cross now?$"

Wasteland_ShoreRoad_Text_FerryWestGo::
	.string "Sign here. And here. And initial\n"
	.string "there.\p"
	.string "Mind the rail. The engine is held\n"
	.string "together by paperwork.$"

Wasteland_ShoreRoad_EventScript_FerryEast::
	lock
	faceplayer
	msgbox Wasteland_ShoreRoad_Text_FerryEastAsk, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Wasteland_ShoreRoad_EventScript_FerryEastNo
	msgbox Wasteland_ShoreRoad_Text_FerryEastGo, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_PLAYER, DIR_EAST
	playse SE_SHIP
	fadescreen FADE_TO_BLACK
	delay 90
	warpsilent MAP_WASTELAND_SHORE_ROAD, 22, 12
	waitstate
	end

Wasteland_ShoreRoad_EventScript_FerryEastNo::
	msgbox Wasteland_ShoreRoad_Text_FerryNo, MSGBOX_DEFAULT
	release
	end

Wasteland_ShoreRoad_Text_FerryEastAsk::
	.string "Ferry back to the west shore.\n"
	.string "Same toll. Same form.\p"
	.string "Cross now?$"

Wasteland_ShoreRoad_Text_FerryEastGo::
	.string "Sign here. And here.\p"
	.string "Hold on. The ferry's older than\n"
	.string "the form.$"

Wasteland_ShoreRoad_Text_FerryNo::
	.string "Suit yourself. The water isn't\n"
	.string "going anywhere.$"

Wasteland_ShoreRoad_EventScript_Patrol1::
	trainerbattle_single TRAINER_SHORE_PATROL_1, Wasteland_ShoreRoad_Text_Patrol1Intro, Wasteland_ShoreRoad_Text_Patrol1Defeat
	msgbox Wasteland_ShoreRoad_Text_Patrol1Post, MSGBOX_AUTOCLOSE
	end

Wasteland_ShoreRoad_Text_Patrol1Intro::
	.string "Nobody walks this shore without\n"
	.string "being counted. You're being\l"
	.string "counted.$"

Wasteland_ShoreRoad_Text_Patrol1Defeat::
	.string "That's a discrepancy.$"

Wasteland_ShoreRoad_Text_Patrol1Post::
	.string "Counted and noted. Keep moving.$"

Wasteland_ShoreRoad_EventScript_Patrol2::
	trainerbattle_single TRAINER_SHORE_PATROL_2, Wasteland_ShoreRoad_Text_Patrol2Intro, Wasteland_ShoreRoad_Text_Patrol2Defeat
	msgbox Wasteland_ShoreRoad_Text_Patrol2Post, MSGBOX_AUTOCLOSE
	end

Wasteland_ShoreRoad_Text_Patrol2Intro::
	.string "Company stink on you. Or is it\n"
	.string "estate? Doesn't matter. Everyone\l"
	.string "pays.$"

Wasteland_ShoreRoad_Text_Patrol2Defeat::
	.string "Hm. Paid, I suppose.$"

Wasteland_ShoreRoad_Text_Patrol2Post::
	.string "The shore's quiet today. Make it\n"
	.string "stay that way.$"

Wasteland_ShoreRoad_EventScript_Scavenger::
	trainerbattle_single TRAINER_SHORE_SCAVENGER, Wasteland_ShoreRoad_Text_ScavengerIntro, Wasteland_ShoreRoad_Text_ScavengerDefeat
	msgbox Wasteland_ShoreRoad_Text_ScavengerPost, MSGBOX_AUTOCLOSE
	end

Wasteland_ShoreRoad_Text_ScavengerIntro::
	.string "Finders keepers, and I found you\n"
	.string "first.$"

Wasteland_ShoreRoad_Text_ScavengerDefeat::
	.string "Fine. Keep your junk.$"

Wasteland_ShoreRoad_Text_ScavengerPost::
	.string "Nothing left on this beach worth\n"
	.string "fighting over. I checked.$"

