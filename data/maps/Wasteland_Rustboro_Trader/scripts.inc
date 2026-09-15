Wasteland_Rustboro_Trader_MapScripts::
	.byte 0

@ Opened 2026-09-15. Reuses real vanilla RustboroCity_House1 verbatim,
@ keeping its real ingame_trade mechanic - reframed around a new custom
@ trade (INGAME_TRADE_WASTELAND_ABSOL, src/data/trade.h) instead of
@ vanilla's Seedot-for-Ralts swap. Absol picked deliberately per Viktor's
@ own choice (2026-09-15): its real Pokédex premise - it senses disaster
@ and tries to warn people, who blame it for causing the disaster instead -
@ mirrors this story's own premise (Pokémon panicking when the control
@ network failed, then getting blamed for a collapse humans caused).
@ Requests a Poochyena in return - something any player will have a spare
@ of by this point (Wasteland_Road's own wild encounter table).
Wasteland_Rustboro_Trader_EventScript_Trader::
	lock
	faceplayer
	goto_if_set FLAG_WASTELAND_RUSTBORO_TRADE_COMPLETED, Wasteland_Rustboro_Trader_EventScript_TradeCompleted
	ingame_trade INGAME_TRADE_WASTELAND_ABSOL, Wasteland_Rustboro_Trader_Text_IllTradeIfYouWant, Wasteland_Rustboro_Trader_EventScript_DeclineTrade, Wasteland_Rustboro_Trader_EventScript_NotRequestedMon, Wasteland_Rustboro_Trader_Text_BeGoodToHer
	setflag FLAG_WASTELAND_RUSTBORO_TRADE_COMPLETED
	release
	end

Wasteland_Rustboro_Trader_EventScript_DeclineTrade::
	msgbox Wasteland_Rustboro_Trader_Text_DeclineTrade, MSGBOX_DEFAULT
	release
	end

Wasteland_Rustboro_Trader_EventScript_NotRequestedMon::
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox Wasteland_Rustboro_Trader_Text_NotRequestedMon, MSGBOX_DEFAULT
	release
	end

Wasteland_Rustboro_Trader_EventScript_TradeCompleted::
	msgbox Wasteland_Rustboro_Trader_Text_TradeCompleted, MSGBOX_DEFAULT
	release
	end

Wasteland_Rustboro_Trader_EventScript_Neighbor::
	lock
	faceplayer
	msgbox Wasteland_Rustboro_Trader_Text_Neighbor, MSGBOX_DEFAULT
	release
	end

Wasteland_Rustboro_Trader_Text_IllTradeIfYouWant::
	.string "Found her two towns over, right\n"
	.string "after a rockslide took out half a\l"
	.string "supply road.\p"
	.string "Everyone said she caused it. I\n"
	.string "watched her try to warn people\l"
	.string "away before it happened.\p"
	.string "Once folks decide something's bad\n"
	.string "luck, that's that. Nobody around\l"
	.string "here will even look at her.\p"
	.string "I'll trade you my {STR_VAR_2} for a\n"
	.string "{STR_VAR_1}, if you want. She\l"
	.string "deserves better than this.$"

Wasteland_Rustboro_Trader_Text_BeGoodToHer::
	.string "Thank you. Really.\p"
	.string "She's not bad luck. She just sees\n"
	.string "it coming before the rest of us do.$"

Wasteland_Rustboro_Trader_Text_DeclineTrade::
	.string "That's fine. I understand.\p"
	.string "But somebody's got to trust her\n"
	.string "eventually.$"

Wasteland_Rustboro_Trader_Text_NotRequestedMon::
	.string "That's not a {STR_VAR_1}.\n"
	.string "I need a {STR_VAR_1} specifically.$"

Wasteland_Rustboro_Trader_Text_TradeCompleted::
	.string "I hope she's doing all right.\p"
	.string "Somewhere people don't flinch when\n"
	.string "she walks in a room, for once.$"

Wasteland_Rustboro_Trader_Text_Neighbor::
	.string "Absol showing up before something\n"
	.string "bad happens?\p"
	.string "Where I'm from, that just means\n"
	.string "you've got about a day to get out.$"
