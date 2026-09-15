Wasteland_Rustboro_PokemonSchool_MapScripts::
	.byte 0

@ Opened 2026-09-15. Reuses real vanilla RustboroCity_PokemonSchool
@ verbatim - all 7 NPCs, the blackboard, and the student notebook sign
@ kept at their real positions. The genuinely useful game-mechanic
@ explanations (status conditions, held items) are kept close to their
@ real vanilla wording since they're accurate regardless of setting; only
@ the framing/flavor lines and Scott (reskinned into a nameless traveling
@ "Scout" who hints at the wider world - see below) were rewritten.
Wasteland_Rustboro_PokemonSchool_EventScript_Blackboard::
	lockall
	msgbox Wasteland_Rustboro_PokemonSchool_Text_BlackboardIntro, MSGBOX_DEFAULT
	goto Wasteland_Rustboro_PokemonSchool_EventScript_ChooseBlackboardTopic
	end

Wasteland_Rustboro_PokemonSchool_EventScript_ChooseBlackboardTopic::
	message Wasteland_Rustboro_PokemonSchool_Text_ReadWhichTopic
	waitmessage
	multichoicegrid 8, 1, MULTI_STATUS_INFO, 3, FALSE
	switch VAR_RESULT
	case 0, Wasteland_Rustboro_PokemonSchool_EventScript_Poison
	case 1, Wasteland_Rustboro_PokemonSchool_EventScript_Paralysis
	case 2, Wasteland_Rustboro_PokemonSchool_EventScript_Sleep
	case 3, Wasteland_Rustboro_PokemonSchool_EventScript_Burn
	case 4, Wasteland_Rustboro_PokemonSchool_EventScript_Freeze
	case 5, Wasteland_Rustboro_PokemonSchool_EventScript_ExitTopicSelect
	case MULTI_B_PRESSED, Wasteland_Rustboro_PokemonSchool_EventScript_ExitTopicSelect
	end

Wasteland_Rustboro_PokemonSchool_EventScript_Poison::
	msgbox Wasteland_Rustboro_PokemonSchool_Text_ExplainPoison, MSGBOX_DEFAULT
	goto Wasteland_Rustboro_PokemonSchool_EventScript_ChooseBlackboardTopic
	end

Wasteland_Rustboro_PokemonSchool_EventScript_Paralysis::
	msgbox Wasteland_Rustboro_PokemonSchool_Text_ExplainParalysis, MSGBOX_DEFAULT
	goto Wasteland_Rustboro_PokemonSchool_EventScript_ChooseBlackboardTopic
	end

Wasteland_Rustboro_PokemonSchool_EventScript_Sleep::
	msgbox Wasteland_Rustboro_PokemonSchool_Text_ExplainSleep, MSGBOX_DEFAULT
	goto Wasteland_Rustboro_PokemonSchool_EventScript_ChooseBlackboardTopic
	end

Wasteland_Rustboro_PokemonSchool_EventScript_Burn::
	msgbox Wasteland_Rustboro_PokemonSchool_Text_ExplainBurn, MSGBOX_DEFAULT
	goto Wasteland_Rustboro_PokemonSchool_EventScript_ChooseBlackboardTopic
	end

Wasteland_Rustboro_PokemonSchool_EventScript_Freeze::
	msgbox Wasteland_Rustboro_PokemonSchool_Text_ExplainFreeze, MSGBOX_DEFAULT
	goto Wasteland_Rustboro_PokemonSchool_EventScript_ChooseBlackboardTopic
	end

Wasteland_Rustboro_PokemonSchool_EventScript_ExitTopicSelect::
	releaseall
	end

Wasteland_Rustboro_PokemonSchool_EventScript_Kid1::
	lock
	faceplayer
	msgbox Wasteland_Rustboro_PokemonSchool_Text_Kid1, MSGBOX_DEFAULT
	release
	end

Wasteland_Rustboro_PokemonSchool_EventScript_Kid2::
	lock
	faceplayer
	msgbox Wasteland_Rustboro_PokemonSchool_Text_Kid2, MSGBOX_DEFAULT
	release
	end

Wasteland_Rustboro_PokemonSchool_EventScript_RichBoy::
	lock
	faceplayer
	msgbox Wasteland_Rustboro_PokemonSchool_Text_RichBoy, MSGBOX_DEFAULT
	release
	end

Wasteland_Rustboro_PokemonSchool_EventScript_Lass::
	lock
	faceplayer
	msgbox Wasteland_Rustboro_PokemonSchool_Text_Lass, MSGBOX_DEFAULT
	release
	end

Wasteland_Rustboro_PokemonSchool_EventScript_SchoolKid::
	lock
	faceplayer
	msgbox Wasteland_Rustboro_PokemonSchool_Text_SchoolKid, MSGBOX_DEFAULT
	release
	end

Wasteland_Rustboro_PokemonSchool_EventScript_StudentNotebook::
	msgbox Wasteland_Rustboro_PokemonSchool_Text_StudentsNotes, MSGBOX_SIGN
	end

Wasteland_Rustboro_PokemonSchool_EventScript_Teacher::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_QUICK_CLAW, Wasteland_Rustboro_PokemonSchool_EventScript_GaveQuickClaw
	msgbox Wasteland_Rustboro_PokemonSchool_Text_TeacherGivesQuickClaw, MSGBOX_DEFAULT
	giveitem ITEM_QUICK_CLAW
	goto_if_eq VAR_RESULT, 0, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_QUICK_CLAW
	release
	end

Wasteland_Rustboro_PokemonSchool_EventScript_GaveQuickClaw::
	msgbox Wasteland_Rustboro_PokemonSchool_Text_ExplainQuickClaw, MSGBOX_DEFAULT
	release
	end

@ Reskinned from vanilla's Scott (a Battle Frontier-specific character not
@ relevant to this story) into a nameless traveling Scout, per the
@ Thirty-first feature entry's confirmed 8-territory story spine - a small,
@ deliberate hint that there's a wider world past Rustboro and Miller's
@ Cut without naming anything specific yet.
Wasteland_Rustboro_PokemonSchool_EventScript_Scout::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_CORP_OVERSEER, Wasteland_Rustboro_PokemonSchool_EventScript_ScoutAfter
	msgbox Wasteland_Rustboro_PokemonSchool_Text_ScoutBefore, MSGBOX_DEFAULT
	release
	end

Wasteland_Rustboro_PokemonSchool_EventScript_ScoutAfter::
	msgbox Wasteland_Rustboro_PokemonSchool_Text_ScoutAfterMsg, MSGBOX_DEFAULT
	release
	end

Wasteland_Rustboro_PokemonSchool_Text_BlackboardIntro::
	.string "The blackboard lists status\n"
	.string "conditions that can affect POKéMON\l"
	.string "in battle.$"

Wasteland_Rustboro_PokemonSchool_Text_ReadWhichTopic::
	.string "Which topic do you want to read?$"

Wasteland_Rustboro_PokemonSchool_Text_ExplainPoison::
	.string "If a POKéMON is poisoned, it will\n"
	.string "steadily lose HP.\p"
	.string "The effects of poison remain after\n"
	.string "a battle.\p"
	.string "A poisoned POKéMON's HP will drop\n"
	.string "while it is traveling.\p"
	.string "Heal a poisoning using an ANTIDOTE.$"

Wasteland_Rustboro_PokemonSchool_Text_ExplainParalysis::
	.string "If a POKéMON becomes paralyzed,\n"
	.string "its SPEED drops.\p"
	.string "It may also not be able to move\n"
	.string "while it is in battle.\p"
	.string "Paralysis remains after battle.\n"
	.string "Cure it using a PARLYZ HEAL.$"

Wasteland_Rustboro_PokemonSchool_Text_ExplainSleep::
	.string "If a POKéMON falls asleep, it will\n"
	.string "be unable to attack.\p"
	.string "A POKéMON may wake up on its own,\n"
	.string "but if a battle ends while it is\l"
	.string "sleeping, it will stay asleep.\p"
	.string "Wake it up using an AWAKENING.$"

Wasteland_Rustboro_PokemonSchool_Text_ExplainBurn::
	.string "A burn reduces ATTACK power, and it\n"
	.string "steadily reduces the victim's HP.\p"
	.string "A burn lingers after battle.\n"
	.string "Cure a burn using a BURN HEAL.$"

Wasteland_Rustboro_PokemonSchool_Text_ExplainFreeze::
	.string "If a POKéMON is frozen, it becomes\n"
	.string "completely helpless.\p"
	.string "It will remain frozen after battle.\n"
	.string "Thaw it out using an ICE HEAL.$"

Wasteland_Rustboro_PokemonSchool_Text_Kid1::
	.string "There's a guy near the flats\n"
	.string "trading a POKéMON everyone's\l"
	.string "scared of.\p"
	.string "I dare you to go look at it.$"

Wasteland_Rustboro_PokemonSchool_Text_Kid2::
	.string "I heard it's not even dangerous.\n"
	.string "People are just jumpy these days.$"

Wasteland_Rustboro_PokemonSchool_Text_RichBoy::
	.string "POKéMON can hold items, but they\n"
	.string "don't know what to do with things\l"
	.string "like potions or antidotes.\p"
	.string "Corporate testing confirmed it.\n"
	.string "Obviously.$"

Wasteland_Rustboro_PokemonSchool_Text_Lass::
	.string "Confused POKéMON sometimes hurt\n"
	.string "themselves instead of attacking.\p"
	.string "It wears off once the battle's\n"
	.string "over, at least.$"

Wasteland_Rustboro_PokemonSchool_Text_SchoolKid::
	.string "A POKéMON holding a BERRY can heal\n"
	.string "itself mid-battle.\p"
	.string "There's a lot to keep track of.\n"
	.string "My notes are a mess.$"

Wasteland_Rustboro_PokemonSchool_Text_StudentsNotes::
	.string "It's this student's notebook.\p"
	.string "POKéMON are caught using\n"
	.string "POKé BALLS.\p"
	.string "Up to six POKéMON can travel with\n"
	.string "a TRAINER at once.\p"
	.string "A TRAINER catches, raises, and\n"
	.string "battles alongside their POKéMON.\p"
	.string "In different handwriting, at the\n"
	.string "bottom: “ask about extra credit\l"
	.string "for Assessment prep.”$"

Wasteland_Rustboro_PokemonSchool_Text_TeacherGivesQuickClaw::
	.string "Students who don't study get a\n"
	.string "taste of my QUICK CLAW.\p"
	.string "Whether you're paying attention\n"
	.string "shows in how you use it.$"

Wasteland_Rustboro_PokemonSchool_Text_ExplainQuickClaw::
	.string "A POKéMON holding the QUICK CLAW\n"
	.string "will occasionally move before its\l"
	.string "opponent.\p"
	.string "There's a lot to learn about held\n"
	.string "items. This is just the start.$"

Wasteland_Rustboro_PokemonSchool_Text_ScoutBefore::
	.string "Rustboro's not much for outside\n"
	.string "news. Every territory guards its\l"
	.string "own.\p"
	.string "Come back once people here start\n"
	.string "taking you seriously. I'll have\l"
	.string "more to say then.$"

Wasteland_Rustboro_PokemonSchool_Text_ScoutAfterMsg::
	.string "Word travels fast, once someone\n"
	.string "like the OVERSEER takes notice of\l"
	.string "you.\p"
	.string "There's more out there than\n"
	.string "RUSTBORO and the CUT - other\l"
	.string "territories, other people running\l"
	.string "things their own way. Corporate,\l"
	.string "warlord, or something else\l"
	.string "entirely.\p"
	.string "Whatever you're looking for,\n"
	.string "you'll go through one of them\l"
	.string "eventually.$"
