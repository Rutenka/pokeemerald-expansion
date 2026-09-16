@ Reuses the real, whole vanilla Route116 layout verbatim (per the standing
@ "no crop-and-stitch, reskin only" rule) - Rustboro's real east neighbor,
@ same secondary tileset (Rustboro) as Wasteland_Rustboro itself, so this
@ connection is zero-risk (matches Wasteland_SouthRoad's own reasoning,
@ which was retired - see below - once its south attachment point turned
@ out to collide with the Corp Checkpoint's real exit trigger there).
@
@ Confirmed via a collision BFS check (not assumed) that Route116's own 5
@ real cuttable trees are all bypassable in vanilla (decorative shortcuts,
@ not a real gate) - kept as real decorative/reward trees further down the
@ road, and a genuine mandatory gate was added instead: 6 more cuttable
@ trees placed side by side across every walkable row of the Rustboro
@ seam (local x=3, y=8-13), the same "physical blockade" technique already
@ proven for the Ashband Lookout in Wasteland_MillersCut, just built from
@ tree objects instead of guard NPCs. This is the HM Cut gate Viktor asked
@ for - confirmed by BFS that no walkable detour around it exists.
@
@ All named NPCs reflavored as travelers/locals on Rustboro's eastern
@ frontier road. The real vanilla cave-mouth door at (47,8) (originally
@ leading to Rusturf Tunnel) is repointed straight into Wasteland_Haverbrook
@ instead - a real, already-tagged door tile, no new tile art needed.
Wasteland_EastRoad_MapScripts::
	.byte 0

Wasteland_EastRoad_EventScript_Arrival::
	setflag FLAG_SEEN_EAST_ROAD_ARRIVAL
	lockall
	msgbox Wasteland_EastRoad_Text_Arrival, MSGBOX_DEFAULT
	releaseall
	end

Wasteland_EastRoad_Text_Arrival::
	.string "The wall of trees ahead wasn't an\n"
	.string "accident. Nobody gets into Haverbrook\l"
	.string "without cutting their own way in\l"
	.string "first.$"

Wasteland_EastRoad_EventScript_Joey::
	lock
	faceplayer
	msgbox Wasteland_EastRoad_Text_Joey, MSGBOX_DEFAULT
	release
	end

Wasteland_EastRoad_Text_Joey::
	.string "Cleared my own path through here\n"
	.string "years back. Grows right back if you\l"
	.string "don't keep at it.$"

Wasteland_EastRoad_EventScript_Jose::
	lock
	faceplayer
	msgbox Wasteland_EastRoad_Text_Jose, MSGBOX_DEFAULT
	release
	end

Wasteland_EastRoad_Text_Jose::
	.string "Bugs out here don't care whose\n"
	.string "territory this is supposed to be.$"

Wasteland_EastRoad_EventScript_Briney::
	lock
	faceplayer
	msgbox Wasteland_EastRoad_Text_Briney, MSGBOX_DEFAULT
	release
	end

Wasteland_EastRoad_Text_Briney::
	.string "Used to run the tunnel routes\n"
	.string "before Rustboro decided who gets to\l"
	.string "travel where. Still know every path\l"
	.string "out here better than they do.$"

Wasteland_EastRoad_EventScript_Clark::
	lock
	faceplayer
	msgbox Wasteland_EastRoad_Text_Clark, MSGBOX_DEFAULT
	release
	end

Wasteland_EastRoad_Text_Clark::
	.string "Haverbrook way? Keep east. You'll\n"
	.string "know it when the road stops asking\l"
	.string "for papers.$"

Wasteland_EastRoad_EventScript_Janice::
	lock
	faceplayer
	msgbox Wasteland_EastRoad_Text_Janice, MSGBOX_DEFAULT
	release
	end

Wasteland_EastRoad_Text_Janice::
	.string "I come out here just to breathe air\n"
	.string "that isn't somebody's property.$"

Wasteland_EastRoad_EventScript_Karen::
	lock
	faceplayer
	msgbox Wasteland_EastRoad_Text_Karen, MSGBOX_DEFAULT
	release
	end

Wasteland_EastRoad_Text_Karen::
	.string "My brother trades in Haverbrook.\n"
	.string "Says the people there actually look\l"
	.string "you in the eye.$"

Wasteland_EastRoad_EventScript_Jerry::
	lock
	faceplayer
	msgbox Wasteland_EastRoad_Text_Jerry, MSGBOX_DEFAULT
	release
	end

Wasteland_EastRoad_Text_Jerry::
	.string "Studying the local POKéMON out\n"
	.string "here. None of them act like the\l"
	.string "ones penned up in the city.$"

Wasteland_EastRoad_EventScript_DevonEmployee::
	lock
	faceplayer
	msgbox Wasteland_EastRoad_Text_DevonEmployee, MSGBOX_DEFAULT
	release
	end

Wasteland_EastRoad_Text_DevonEmployee::
	.string "Officially I'm off duty. Officially\n"
	.string "I'm not supposed to be this far out\l"
	.string "either. Small world.$"

Wasteland_EastRoad_EventScript_Marcus::
	lock
	faceplayer
	msgbox Wasteland_EastRoad_Text_Marcus, MSGBOX_DEFAULT
	release
	end

Wasteland_EastRoad_Text_Marcus::
	.string "Training out here where nobody's\n"
	.string "keeping score. Suits me fine.$"

Wasteland_EastRoad_EventScript_GlassesMan::
	lock
	faceplayer
	msgbox Wasteland_EastRoad_Text_GlassesMan, MSGBOX_DEFAULT
	release
	end

Wasteland_EastRoad_Text_GlassesMan::
	.string "Rumor is there's a whole second\n"
	.string "route past Haverbrook nobody's\l"
	.string "mapped properly. Rumor, mind you.$"

Wasteland_EastRoad_EventScript_Sarah::
	lock
	faceplayer
	msgbox Wasteland_EastRoad_Text_Sarah, MSGBOX_DEFAULT
	release
	end

Wasteland_EastRoad_Text_Sarah::
	.string "Long walk from Rustboro. Longer\n"
	.string "one back, usually.$"

Wasteland_EastRoad_EventScript_Dawson::
	lock
	faceplayer
	msgbox Wasteland_EastRoad_Text_Dawson, MSGBOX_DEFAULT
	release
	end

Wasteland_EastRoad_Text_Dawson::
	.string "Found a whole nest of berries out\n"
	.string "past those trees. Worth the walk.$"

Wasteland_EastRoad_EventScript_Johnson::
	lock
	faceplayer
	msgbox Wasteland_EastRoad_Text_Johnson, MSGBOX_DEFAULT
	release
	end

Wasteland_EastRoad_Text_Johnson::
	.string "Nobody patrols out here. That's\n"
	.string "either the best or worst thing\l"
	.string "about it, depending on the day.$"

Wasteland_EastRoad_EventScript_Devan::
	lock
	faceplayer
	msgbox Wasteland_EastRoad_Text_Devan, MSGBOX_DEFAULT
	release
	end

Wasteland_EastRoad_Text_Devan::
	.string "Cave's just ahead. Haverbrook's\n"
	.string "right through it, if the door hasn't\l"
	.string "changed its mind about you.$"

Wasteland_EastRoad_EventScript_SignRustboro::
	msgbox Wasteland_EastRoad_Text_SignRustboro, MSGBOX_SIGN
	end

Wasteland_EastRoad_Text_SignRustboro::
	.string "RUSTBORO - Devon Corporation\n"
	.string "regional seat. Assessment\l"
	.string "required for entry.$"

Wasteland_EastRoad_EventScript_SignHaverbrook::
	msgbox Wasteland_EastRoad_Text_SignHaverbrook, MSGBOX_SIGN
	end

Wasteland_EastRoad_Text_SignHaverbrook::
	.string "HAVERBROOK, through the cave -\n"
	.string "independent, and proud of it.$"
