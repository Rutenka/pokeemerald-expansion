Wasteland_Rustboro_Flat1_MapScripts::
	.byte 0

@ Opened 2026-09-15, part of unlocking Rustboro's remaining closed
@ buildings. Reuses the real vanilla RustboroCity_Flat1_1F layout verbatim
@ (per checklist item 11); only dialogue is reflavored. Pure flavor - a
@ small, deliberately understated hint that Devon Corp isn't a place its
@ own employees feel safe being honest about, seeding the "the company
@ isn't a monolith" thread from the Thirty-first feature entry's story
@ spine without spelling anything out.
Wasteland_Rustboro_Flat1_EventScript_Man::
	lock
	faceplayer
	msgbox Wasteland_Rustboro_Flat1_Text_Man, MSGBOX_DEFAULT
	release
	end

Wasteland_Rustboro_Flat1_EventScript_Woman::
	lock
	faceplayer
	msgbox Wasteland_Rustboro_Flat1_Text_Woman, MSGBOX_DEFAULT
	release
	end

Wasteland_Rustboro_Flat1_Text_Man::
	.string "Filed a report last week.\n"
	.string "Haven't heard back.\p"
	.string "Learned a while ago not to ask\n"
	.string "twice.$"

Wasteland_Rustboro_Flat1_Text_Woman::
	.string "He doesn't talk about work anymore.\p"
	.string "I used to ask. I don't, either,\n"
	.string "these days.$"
