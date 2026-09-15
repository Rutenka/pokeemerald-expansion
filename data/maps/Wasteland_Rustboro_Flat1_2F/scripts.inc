Wasteland_Rustboro_Flat1_2F_MapScripts::
	.byte 0

@ Opened 2026-09-15, completing Flat1's upstairs per Viktor's request.
@ Reuses real vanilla RustboroCity_Flat1_2F verbatim, including its real
@ "Walda" minigame (name a funny phrase, see if the baby laughs, get a new
@ PC box wallpaper as thanks) - a self-contained, harmless side activity
@ that doesn't touch the story either way, so kept close to vanilla rather
@ than reinvented. The "one of Devon Corporation's top researchers" line
@ already fit this setting without changes.
Wasteland_Rustboro_Flat1_2F_EventScript_Dad::
	lock
	faceplayer
	specialvar VAR_RESULT, TryBufferWaldaPhrase
	goto_if_eq VAR_RESULT, FALSE, Wasteland_Rustboro_Flat1_2F_EventScript_DadFirstPhrase
	goto_if_eq VAR_RESULT, TRUE, Wasteland_Rustboro_Flat1_2F_EventScript_DadNewPhrase

Wasteland_Rustboro_Flat1_2F_EventScript_GivePhrase::
	special DoWaldaNamingScreen
	goto_if_eq VAR_0x8004, 1, Wasteland_Rustboro_Flat1_2F_EventScript_CancelGivePhrase
	goto_if_eq VAR_0x8004, 2, Wasteland_Rustboro_Flat1_2F_EventScript_CancelGiveFirstPhrase
	specialvar VAR_RESULT, TryGetWallpaperWithWaldaPhrase
	goto_if_eq VAR_RESULT, TRUE, Wasteland_Rustboro_Flat1_2F_EventScript_WaldaLikesPhrase
	goto_if_eq VAR_RESULT, FALSE, Wasteland_Rustboro_Flat1_2F_EventScript_WaldaDoesntLikePhrase
	end

Wasteland_Rustboro_Flat1_2F_EventScript_DadFirstPhrase::
	msgbox Wasteland_Rustboro_Flat1_2F_Text_DoYouKnowFunnyPhrase, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Wasteland_Rustboro_Flat1_2F_EventScript_DeclineGivePhrase
	msgbox Wasteland_Rustboro_Flat1_2F_Text_WonderfulLetsHear, MSGBOX_DEFAULT
	goto Wasteland_Rustboro_Flat1_2F_EventScript_GivePhrase

Wasteland_Rustboro_Flat1_2F_EventScript_DadNewPhrase::
	msgbox Wasteland_Rustboro_Flat1_2F_Text_BeenSayingXBetterPhrase, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Wasteland_Rustboro_Flat1_2F_EventScript_DeclineGivePhrase
	msgbox Wasteland_Rustboro_Flat1_2F_Text_WonderfulLetsHear, MSGBOX_DEFAULT
	goto Wasteland_Rustboro_Flat1_2F_EventScript_GivePhrase

Wasteland_Rustboro_Flat1_2F_EventScript_DeclineGivePhrase::
	msgbox Wasteland_Rustboro_Flat1_2F_Text_OhIsThatRight, MSGBOX_DEFAULT
	release
	end

Wasteland_Rustboro_Flat1_2F_EventScript_CancelGivePhrase::
	msgbox Wasteland_Rustboro_Flat1_2F_Text_OhYouDontKnowAny, MSGBOX_DEFAULT
	release
	end

Wasteland_Rustboro_Flat1_2F_EventScript_CancelGiveFirstPhrase::
	msgbox Wasteland_Rustboro_Flat1_2F_Text_ThinkOfMyOwnPhrase, MSGBOX_DEFAULT
	call Wasteland_Rustboro_Flat1_2F_EventScript_DadFaceWalda
	msgbox Wasteland_Rustboro_Flat1_2F_Text_NotSmilingAtAll2, MSGBOX_DEFAULT
	release
	end

Wasteland_Rustboro_Flat1_2F_EventScript_WaldaLikesPhrase::
	msgbox Wasteland_Rustboro_Flat1_2F_Text_LetsGiveItATry2, MSGBOX_DEFAULT
	call Wasteland_Rustboro_Flat1_2F_EventScript_DadFaceWalda
	msgbox Wasteland_Rustboro_Flat1_2F_Text_OhShesLaughing, MSGBOX_DEFAULT
	applymovement LOCALID_WASTELAND_WALDAS_DAD, Common_Movement_FacePlayer
	waitmovement 0
	msgbox Wasteland_Rustboro_Flat1_2F_Text_ThankYouWallpaper, MSGBOX_DEFAULT
	release
	end

Wasteland_Rustboro_Flat1_2F_EventScript_WaldaDoesntLikePhrase::
	msgbox Wasteland_Rustboro_Flat1_2F_Text_LetsGiveItATry, MSGBOX_DEFAULT
	call Wasteland_Rustboro_Flat1_2F_EventScript_DadFaceWalda
	msgbox Wasteland_Rustboro_Flat1_2F_Text_NotSmilingAtAll, MSGBOX_DEFAULT
	release
	end

Wasteland_Rustboro_Flat1_2F_EventScript_DadFaceWalda::
	turnobject LOCALID_WASTELAND_WALDAS_DAD, DIR_EAST
	return

Wasteland_Rustboro_Flat1_2F_EventScript_Mom::
	msgbox Wasteland_Rustboro_Flat1_2F_Text_ComingUpWithMealsIsHard, MSGBOX_NPC
	end

Wasteland_Rustboro_Flat1_2F_EventScript_PokeDoll::
	msgbox Wasteland_Rustboro_Flat1_2F_Text_PlushDoll, MSGBOX_SIGN
	end

Wasteland_Rustboro_Flat1_2F_Text_ComingUpWithMealsIsHard::
	.string "Oh, it's so hard every day…\p"
	.string "Trying to figure out what to make\n"
	.string "for meals, with what's actually\l"
	.string "available.\p"
	.string "It really isn't easy.$"

Wasteland_Rustboro_Flat1_2F_Text_DoYouKnowFunnyPhrase::
	.string "Oh, hello! Welcome to the PEPPER\n"
	.string "household.\p"
	.string "I have a question for you. Have you\n"
	.string "ever looked after a baby?\p"
	.string "My daughter WALDA doesn't laugh\n"
	.string "enough. I think she'd laugh if I\l"
	.string "told her something funny.\p"
	.string "Do you know of a funny word or\n"
	.string "phrase you can tell me?$"

Wasteland_Rustboro_Flat1_2F_Text_BeenSayingXBetterPhrase::
	.string "I've been saying “{STR_VAR_1}”\n"
	.string "to amuse her lately.\p"
	.string "Do you know a better word or\n"
	.string "phrase that might work?$"

Wasteland_Rustboro_Flat1_2F_Text_WonderfulLetsHear::
	.string "Oh, that's wonderful.\n"
	.string "So, let's hear it, your suggestion.$"

Wasteland_Rustboro_Flat1_2F_Text_OhIsThatRight::
	.string "Oh, is that right?\p"
	.string "Well, if you come up with a good\n"
	.string "suggestion, I'm all ears.$"

Wasteland_Rustboro_Flat1_2F_Text_LetsGiveItATry2::
	.string "Ah, I see.\n"
	.string "Well, let's give it a try, shall we?$"

Wasteland_Rustboro_Flat1_2F_Text_OhShesLaughing::
	.string "{STR_VAR_1}.\n"
	.string "{STR_VAR_1}.\p"
	.string "Oh, yes! She's laughing!\n"
	.string "Oh, I am as delighted as she!$"

Wasteland_Rustboro_Flat1_2F_Text_LetsGiveItATry::
	.string "Ah, I see.\n"
	.string "Well, let's give it a try, shall we?$"

Wasteland_Rustboro_Flat1_2F_Text_NotSmilingAtAll::
	.string "{STR_VAR_1}.\n"
	.string "{STR_VAR_1}.\p"
	.string "Hmmm… She's not smiling at all.\n"
	.string "Maybe WALDA is one serious child…$"

Wasteland_Rustboro_Flat1_2F_Text_ThinkOfMyOwnPhrase::
	.string "Oh, so you don't know any good\n"
	.string "words. I'd better think for myself,\l"
	.string "then.\p"
	.string "Hmm…\n"
	.string "How about “{STR_VAR_1}”?\l"
	.string "Let's see if that will work.$"

Wasteland_Rustboro_Flat1_2F_Text_NotSmilingAtAll2::
	.string "{STR_VAR_1}.\n"
	.string "{STR_VAR_1}.\p"
	.string "Hmmm… She's not smiling at all.\n"
	.string "Maybe WALDA is one serious child…$"

Wasteland_Rustboro_Flat1_2F_Text_OhYouDontKnowAny::
	.string "Oh, so you don't know any good\n"
	.string "words. I guess I'll try the saying\l"
	.string "I used before.\p"
	.string "Anyways, if you have a good\n"
	.string "suggestion, don't hesitate to tell\l"
	.string "me, okay?$"

Wasteland_Rustboro_Flat1_2F_Text_ThankYouWallpaper::
	.string "Thank you!\p"
	.string "Thanks to you, my darling WALDA\n"
	.string "laughed for me!\p"
	.string "Actually, I may not look all that\n"
	.string "special, but I'm one of DEVON\l"
	.string "CORPORATION's top researchers.\p"
	.string "So, how about I do something in\n"
	.string "return for you?\p"
	.string "I'll add some new wallpaper\n"
	.string "patterns for the BOXES in the PC\l"
	.string "POKéMON Storage System.\p"
	.string "In the wallpaper pattern menu,\n"
	.string "select “FRIENDS.”\p"
	.string "That will give you access to the\n"
	.string "new wallpaper patterns.$"

Wasteland_Rustboro_Flat1_2F_Text_PlushDoll::
	.string "It's a POKéMON plush DOLL!$"
