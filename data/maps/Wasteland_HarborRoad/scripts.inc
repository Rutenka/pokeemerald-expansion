Wasteland_HarborRoad_MapScripts::
	.byte 0

Wasteland_HarborRoad_EventScript_Camper::
	lock
	faceplayer
	msgbox Wasteland_HarborRoad_Text_Camper, MSGBOX_DEFAULT
	release
	end

Wasteland_HarborRoad_Text_Camper::
	.string "You can smell the harbor from\n"
	.string "here. Salt, diesel, and\l"
	.string "paperwork.$"

Wasteland_HarborRoad_EventScript_OldWoman::
	lock
	faceplayer
	msgbox Wasteland_HarborRoad_Text_OldWoman, MSGBOX_DEFAULT
	release
	end

Wasteland_HarborRoad_Text_OldWoman::
	.string "I walk this road every day. If I\n"
	.string "stop, someone will put me on a\l"
	.string "list.$"

Wasteland_HarborRoad_EventScript_OldMan::
	lock
	faceplayer
	msgbox Wasteland_HarborRoad_Text_OldMan, MSGBOX_DEFAULT
	release
	end

Wasteland_HarborRoad_Text_OldMan::
	.string "North's closed. Quarantine, they\n"
	.string "say. Nobody says quarantined\l"
	.string "against what.$"

Wasteland_HarborRoad_EventScript_Boy::
	lock
	faceplayer
	msgbox Wasteland_HarborRoad_Text_Boy, MSGBOX_DEFAULT
	release
	end

Wasteland_HarborRoad_Text_Boy::
	.string "Went north once to see. Someone\n"
	.string "told me very politely to leave. I\l"
	.string "left very politely.$"

Wasteland_HarborRoad_EventScript_PortSign::
	msgbox Wasteland_HarborRoad_Text_PortSign, MSGBOX_SIGN
	end

Wasteland_HarborRoad_Text_PortSign::
	.string "THE PORT. Harbor ahead.\p"
	.string "Registration on arrival is\n"
	.string "mandatory, free, and binding.$"

Wasteland_HarborRoad_EventScript_ShoreSign::
	msgbox Wasteland_HarborRoad_Text_ShoreSign, MSGBOX_SIGN
	end

Wasteland_HarborRoad_Text_ShoreSign::
	.string "SHORE ROAD, west. The Crossing\n"
	.string "beyond.$"

Wasteland_HarborRoad_EventScript_MauvilleSign::
	msgbox Wasteland_HarborRoad_Text_MauvilleSign, MSGBOX_SIGN
	end

Wasteland_HarborRoad_Text_MauvilleSign::
	.string "MAUVILLE. ROAD CLOSED.\p"
	.string "By order of the wardens. Turn\n"
	.string "back.$"

Wasteland_HarborRoad_EventScript_Dockhand::
	trainerbattle_single TRAINER_HARBOR_DOCKHAND, Wasteland_HarborRoad_Text_DockhandIntro, Wasteland_HarborRoad_Text_DockhandDefeat
	msgbox Wasteland_HarborRoad_Text_DockhandPost, MSGBOX_AUTOCLOSE
	end

Wasteland_HarborRoad_Text_DockhandIntro::
	.string "Docks are that way. You are not\n"
	.string "going that way without my say.$"

Wasteland_HarborRoad_Text_DockhandDefeat::
	.string "Right. You can go.$"

Wasteland_HarborRoad_Text_DockhandPost::
	.string "Fine. Docks are still that way.$"

Wasteland_HarborRoad_EventScript_Angler::
	trainerbattle_single TRAINER_HARBOR_ANGLER, Wasteland_HarborRoad_Text_AnglerIntro, Wasteland_HarborRoad_Text_AnglerDefeat
	msgbox Wasteland_HarborRoad_Text_AnglerPost, MSGBOX_AUTOCLOSE
	end

Wasteland_HarborRoad_Text_AnglerIntro::
	.string "Fish don't bite anymore. People\n"
	.string "do. Come on.$"

Wasteland_HarborRoad_Text_AnglerDefeat::
	.string "Nothing biting today.$"

Wasteland_HarborRoad_Text_AnglerPost::
	.string "Go on down to the harbor. I'll\n"
	.string "keep fishing.$"

Wasteland_HarborRoad_EventScript_Patrol::
	trainerbattle_single TRAINER_HARBOR_PATROL, Wasteland_HarborRoad_Text_PatrolIntro, Wasteland_HarborRoad_Text_PatrolDefeat
	msgbox Wasteland_HarborRoad_Text_PatrolPost, MSGBOX_AUTOCLOSE
	end

Wasteland_HarborRoad_Text_PatrolIntro::
	.string "Everyone who comes down this road\n"
	.string "reaches the harbor. You reach it\l"
	.string "after me.$"

Wasteland_HarborRoad_Text_PatrolDefeat::
	.string "That's an inconvenience.$"

Wasteland_HarborRoad_Text_PatrolPost::
	.string "Harbor's ahead. Register or\n"
	.string "don't. It won't matter.$"

