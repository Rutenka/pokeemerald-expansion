@ Reuses RustboroCity_Gym's real layout and NPC positions verbatim - only
@ the people and dialogue changed. Reflavored as the corporate settlement's
@ "assessment center": a formal, bureaucratic framing over what is, in
@ practice, the game's first real boss gauntlet - fits the design brief's
@ "absurd humor from bureaucracy" note while still playing as a real fight.
Wasteland_RustboroGym_MapScripts::
	.byte 0

Wasteland_RustboroGym_EventScript_Overseer::
	trainerbattle_single TRAINER_CORP_OVERSEER, Wasteland_RustboroGym_Text_OverseerIntro, Wasteland_RustboroGym_Text_OverseerDefeat, Wasteland_RustboroGym_EventScript_OverseerDefeated, NO_MUSIC
	msgbox Wasteland_RustboroGym_Text_OverseerPostBattle, MSGBOX_DEFAULT
	release
	end

Wasteland_RustboroGym_EventScript_OverseerDefeated::
	msgbox Wasteland_RustboroGym_Text_OverseerCertify, MSGBOX_DEFAULT
	setflag FLAG_DEFEATED_CORP_OVERSEER
	@ Added 2026-09-15 alongside opening Rustboro's remaining houses: HM
	@ field moves (Cut, etc.) are gated on the matching real badge flag
	@ (src/field_move.c; FLAG_BADGE01_GET for Cut specifically) regardless
	@ of whether this story uses gym badges - without this, the free HM
	@ Cut from Wasteland_Rustboro_CuttersHouse would be permanently
	@ unusable in the field. Tied to actually winning this fight (not
	@ merely being granted clearance to challenge it), matching real
	@ vanilla's own logic: the badge comes from beating the Gym Leader,
	@ not from being let through the door.
	setflag FLAG_BADGE01_GET
	giveitem ITEM_TM_SHOCK_WAVE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	msgbox Wasteland_RustboroGym_Text_OverseerGiveTM, MSGBOX_DEFAULT
	release
	end

Wasteland_RustboroGym_EventScript_Trainer1::
	trainerbattle_single TRAINER_CORP_TRAINER_1, Wasteland_RustboroGym_Text_Trainer1Intro, Wasteland_RustboroGym_Text_Trainer1Defeat
	msgbox Wasteland_RustboroGym_Text_Trainer1PostBattle, MSGBOX_AUTOCLOSE
	end

Wasteland_RustboroGym_EventScript_Trainer2::
	trainerbattle_single TRAINER_CORP_TRAINER_2, Wasteland_RustboroGym_Text_Trainer2Intro, Wasteland_RustboroGym_Text_Trainer2Defeat
	msgbox Wasteland_RustboroGym_Text_Trainer2PostBattle, MSGBOX_AUTOCLOSE
	end

Wasteland_RustboroGym_EventScript_Trainer3::
	trainerbattle_single TRAINER_CORP_TRAINER_3, Wasteland_RustboroGym_Text_Trainer3Intro, Wasteland_RustboroGym_Text_Trainer3Defeat
	msgbox Wasteland_RustboroGym_Text_Trainer3PostBattle, MSGBOX_AUTOCLOSE
	end

Wasteland_RustboroGym_EventScript_Guide::
	lock
	faceplayer
	msgbox Wasteland_RustboroGym_Text_Guide, MSGBOX_DEFAULT
	release
	end

Wasteland_RustboroGym_EventScript_LeftStatue::
	msgbox Wasteland_RustboroGym_Text_LeftStatue, MSGBOX_SIGN
	end

Wasteland_RustboroGym_EventScript_RightStatue::
	msgbox Wasteland_RustboroGym_Text_RightStatue, MSGBOX_SIGN
	end

Wasteland_RustboroGym_Text_OverseerIntro::
	.string "OVERSEER REYES: A challenger.\p"
	.string "Fine. Let's call this a Field\n"
	.string "Aptitude Assessment.\p"
	.string "Try not to take it personally.$"

Wasteland_RustboroGym_Text_OverseerDefeat::
	.string "Noted. Assessment... incomplete.$"

Wasteland_RustboroGym_Text_OverseerCertify::
	.string "OVERSEER REYES: Hm.\p"
	.string "Whatever they trained you on out\n"
	.string "there, it isn't in our manuals.\p"
	.string "I'll file this as a pass. Someone\l"
	.string "above me can decide what that means.$"

Wasteland_RustboroGym_Text_OverseerGiveTM::
	.string "Take this. Consider it a certificate\n"
	.string "with better utility.$"

Wasteland_RustboroGym_Text_OverseerPostBattle::
	.string "OVERSEER REYES: The paperwork's\n"
	.string "already filed. Don't make me redo it.$"

Wasteland_RustboroGym_Text_Trainer1Intro::
	.string "KESSLER: You're not on today's\n"
	.string "visitor list. Assessment stands.$"

Wasteland_RustboroGym_Text_Trainer1Defeat::
	.string "KESSLER: I'll note the deviation.$"

Wasteland_RustboroGym_Text_Trainer1PostBattle::
	.string "KESSLER: The MAGNEMITE don't hold\n"
	.string "grudges. I checked. Twice.$"

Wasteland_RustboroGym_Text_Trainer2Intro::
	.string "PRIYA: Standard procedure. Please\n"
	.string "don't make this a whole thing.$"

Wasteland_RustboroGym_Text_Trainer2Defeat::
	.string "PRIYA: Logged. Moving on.$"

Wasteland_RustboroGym_Text_Trainer2PostBattle::
	.string "PRIYA: BALTOY's older than this\n"
	.string "building. Try not to think about it.$"

Wasteland_RustboroGym_Text_Trainer3Intro::
	.string "DRUMMOND: Between you and me, I\n"
	.string "didn't apply for this job.\p"
	.string "But here we are.$"

Wasteland_RustboroGym_Text_Trainer3Defeat::
	.string "DRUMMOND: Yeah. Fair enough.$"

Wasteland_RustboroGym_Text_Trainer3PostBattle::
	.string "DRUMMOND: Honestly? Good for you.$"

Wasteland_RustboroGym_Text_Guide::
	.string "Officially, this is an aptitude\n"
	.string "testing center.\p"
	.string "Unofficially, everyone still just\l"
	.string "calls it the GYM.$"

Wasteland_RustboroGym_Text_LeftStatue::
	.string "A STONE STATUE.\n"
	.string "It predates the company sign.$"

Wasteland_RustboroGym_Text_RightStatue::
	.string "A STONE STATUE.\n"
	.string "Someone taped a memo to its base.$"
