@ Reuses the real, whole vanilla Route104 layout verbatim (per the standing
@ "no crop-and-stitch, reskin only" rule) - the real vanilla connection
@ south of RustboroCity, same secondary tileset (Rustboro) as
@ Wasteland_Rustboro itself, so the new map `connection` at the seam is
@ zero-risk (same tileset both sides, per the Eleventh feature entry's own
@ root-cause finding). The real, already-placed cuttable tree (local
@ (35,22)) is kept exactly as vanilla has it - this is the HM Cut gate
@ Viktor asked for, not invented content. All named NPCs reflavored as
@ travelers on the road between Rustboro and Haverbrook; berry trees, item
@ balls, and hidden items kept as pure mechanics, unchanged. The Rival
@ cutscene pair and Mr. Briney's boat NPC were dropped (not relevant to this
@ story). Mr. Briney's House and the Pretty Petal Flower Shop doors are
@ deliberately left unwired for now, same "closed for now" trade-off used
@ throughout this project.
Wasteland_SouthRoad_MapScripts::
	.byte 0

Wasteland_SouthRoad_EventScript_Arrival::
	setflag FLAG_SEEN_SOUTH_ROAD_ARRIVAL
	lockall
	msgbox Wasteland_SouthRoad_Text_Arrival, MSGBOX_DEFAULT
	releaseall
	end

Wasteland_SouthRoad_Text_Arrival::
	.string "Rustboro's noise fades fast once\n"
	.string "you're past the wall.\p"
	.string "The road south is quieter - real\n"
	.string "dirt, real trees, nobody watching\l"
	.string "from a camera bracket.\p"
	.string "Somewhere past here, people are\n"
	.string "still running things without\l"
	.string "asking anyone's permission.$"

Wasteland_SouthRoad_EventScript_BugCatcher::
	lock
	faceplayer
	msgbox Wasteland_SouthRoad_Text_BugCatcher, MSGBOX_DEFAULT
	release
	end

Wasteland_SouthRoad_Text_BugCatcher::
	.string "Rustboro doesn't let you catch\n"
	.string "anything without a permit. Out\l"
	.string "here, nobody's stopping me.$"

Wasteland_SouthRoad_EventScript_Girl1::
	lock
	faceplayer
	msgbox Wasteland_SouthRoad_Text_Girl1, MSGBOX_DEFAULT
	release
	end

Wasteland_SouthRoad_Text_Girl1::
	.string "We left the city when the Overseer\n"
	.string "started asking too many questions\l"
	.string "about who my dad talks to.$"

Wasteland_SouthRoad_EventScript_Haley::
	lock
	faceplayer
	msgbox Wasteland_SouthRoad_Text_Haley, MSGBOX_DEFAULT
	release
	end

Wasteland_SouthRoad_Text_Haley::
	.string "Haverbrook doesn't answer to\n"
	.string "Rustboro or anyone out east. That's\l"
	.string "the whole point of the place.$"

Wasteland_SouthRoad_EventScript_Boy1::
	lock
	faceplayer
	msgbox Wasteland_SouthRoad_Text_Boy1, MSGBOX_DEFAULT
	release
	end

Wasteland_SouthRoad_Text_Boy1::
	.string "Garrick keeps the road clear of\n"
	.string "trouble. Don't ask me how - he\l"
	.string "just does.$"

Wasteland_SouthRoad_EventScript_Woman::
	lock
	faceplayer
	msgbox Wasteland_SouthRoad_Text_Woman, MSGBOX_DEFAULT
	release
	end

Wasteland_SouthRoad_Text_Woman::
	.string "Traders come through here both\n"
	.string "ways - Rustboro's goods for\l"
	.string "Haverbrook's grain. Nobody's gone\l"
	.string "hungry on this road yet.$"

Wasteland_SouthRoad_EventScript_Girl2::
	lock
	faceplayer
	msgbox Wasteland_SouthRoad_Text_Girl2, MSGBOX_DEFAULT
	release
	end

Wasteland_SouthRoad_Text_Girl2::
	.string "Almost there. You can smell the\n"
	.string "farms before you see them.$"

Wasteland_SouthRoad_EventScript_Ivan::
	lock
	faceplayer
	msgbox Wasteland_SouthRoad_Text_Ivan, MSGBOX_DEFAULT
	release
	end

Wasteland_SouthRoad_Text_Ivan::
	.string "Caught three good ones off this\n"
	.string "bank last week. Whatever's wrong\l"
	.string "with the world, the fish don't\l"
	.string "seem to know it yet.$"

Wasteland_SouthRoad_EventScript_ExpertF::
	lock
	faceplayer
	msgbox Wasteland_SouthRoad_Text_ExpertF, MSGBOX_DEFAULT
	release
	end

Wasteland_SouthRoad_Text_ExpertF::
	.string "I train out here specifically\n"
	.string "because nobody's grading me on\l"
	.string "it.$"

Wasteland_SouthRoad_EventScript_Florist::
	lock
	faceplayer
	msgbox Wasteland_SouthRoad_Text_Florist, MSGBOX_DEFAULT
	release
	end

Wasteland_SouthRoad_Text_Florist::
	.string "The shop's closed today. Come\n"
	.string "back when I'm not elbow-deep in\l"
	.string "White Herb stock.$"

Wasteland_SouthRoad_EventScript_Gina::
	lock
	faceplayer
	msgbox Wasteland_SouthRoad_Text_Gina, MSGBOX_DEFAULT
	release
	end

Wasteland_SouthRoad_Text_Gina::
	.string "Bet you can't guess which of us\n"
	.string "is older!$"

Wasteland_SouthRoad_EventScript_Mia::
	lock
	faceplayer
	msgbox Wasteland_SouthRoad_Text_Mia, MSGBOX_DEFAULT
	release
	end

Wasteland_SouthRoad_Text_Mia::
	.string "She always says that. It's me,\n"
	.string "by four minutes.$"

Wasteland_SouthRoad_EventScript_Winston::
	lock
	faceplayer
	msgbox Wasteland_SouthRoad_Text_Winston, MSGBOX_DEFAULT
	release
	end

Wasteland_SouthRoad_Text_Winston::
	.string "My family used to summer near\n"
	.string "here. Now it's just where we\l"
	.string "live.$"

Wasteland_SouthRoad_EventScript_Cindy::
	lock
	faceplayer
	msgbox Wasteland_SouthRoad_Text_Cindy, MSGBOX_DEFAULT
	release
	end

Wasteland_SouthRoad_Text_Cindy::
	.string "Watch the tall grass. It's not all\n"
	.string "Zigzagoon out here.$"

Wasteland_SouthRoad_EventScript_Billy::
	lock
	faceplayer
	msgbox Wasteland_SouthRoad_Text_Billy, MSGBOX_DEFAULT
	release
	end

Wasteland_SouthRoad_Text_Billy::
	.string "First time out of the city. It's\n"
	.string "so QUIET.$"

Wasteland_SouthRoad_EventScript_Boy2::
	lock
	faceplayer
	msgbox Wasteland_SouthRoad_Text_Boy2, MSGBOX_DEFAULT
	release
	end

Wasteland_SouthRoad_Text_Boy2::
	.string "That tree won't cut itself. Good\n"
	.string "thing you've got the tool for it.$"

Wasteland_SouthRoad_EventScript_Darian::
	lock
	faceplayer
	msgbox Wasteland_SouthRoad_Text_Darian, MSGBOX_DEFAULT
	release
	end

Wasteland_SouthRoad_Text_Darian::
	.string "Come far?\p"
	.string "You've got that look. Haverbrook's\n"
	.string "the kind of place that fixes it,\l"
	.string "if anything can.$"

Wasteland_SouthRoad_EventScript_CottageSign::
	msgbox Wasteland_SouthRoad_Text_CottageSign, MSGBOX_SIGN
	end

Wasteland_SouthRoad_Text_CottageSign::
	.string "A weathered cottage sits back from\n"
	.string "the road. The door is locked.$"

Wasteland_SouthRoad_EventScript_SignHaverbrook::
	msgbox Wasteland_SouthRoad_Text_SignHaverbrook, MSGBOX_SIGN
	end

Wasteland_SouthRoad_Text_SignHaverbrook::
	.string "HAVERBROOK - independent, and\n"
	.string "proud of it.$"

Wasteland_SouthRoad_EventScript_SignRustboro::
	msgbox Wasteland_SouthRoad_Text_SignRustboro, MSGBOX_SIGN
	end

Wasteland_SouthRoad_Text_SignRustboro::
	.string "RUSTBORO - Devon Corporation\n"
	.string "regional seat. Assessment\l"
	.string "required for entry.$"

Wasteland_SouthRoad_EventScript_FlowerShopSign::
	msgbox Wasteland_SouthRoad_Text_FlowerShopSign, MSGBOX_SIGN
	end

Wasteland_SouthRoad_Text_FlowerShopSign::
	.string "A hand-painted sign: “Pretty Petal\n"
	.string "- closed until further notice.”$"

Wasteland_SouthRoad_EventScript_TipsSign::
	msgbox Wasteland_SouthRoad_Text_TipsSign, MSGBOX_SIGN
	end

Wasteland_SouthRoad_Text_TipsSign::
	.string "A trader's notice board, mostly\n"
	.string "blank. One scrap left: “Bring\l"
	.string "spares. Everything trades out\l"
	.string "here.”$"
