Wasteland_Port_MapScripts::
	.byte 0

Wasteland_Port_EventScript_Foreman::
	lock
	faceplayer
	msgbox Wasteland_Port_Text_Foreman, MSGBOX_DEFAULT
	release
	end

Wasteland_Port_Text_Foreman::
	.string "Fees are posted. If you can't\n"
	.string "read, ask a warden. If you can't\l"
	.string "ask a warden, that's a fee.$"

Wasteland_Port_EventScript_Register::
	lock
	faceplayer
	msgbox Wasteland_Port_Text_Register, MSGBOX_DEFAULT
	release
	end

Wasteland_Port_Text_Register::
	.string "The Harbormaster keeps a\n"
	.string "register. Every name, every date,\l"
	.string "every last seen. Some people\l"
	.string "laugh. Then they lose someone and\l"
	.string "stop.$"

Wasteland_Port_EventScript_Truck::
	lock
	faceplayer
	msgbox Wasteland_Port_Text_Truck, MSGBOX_DEFAULT
	release
	end

Wasteland_Port_Text_Truck::
	.string "My father drove for the company.\n"
	.string "Won't say what was in the trucks.\l"
	.string "He locks the door when it rains.$"

Wasteland_Port_EventScript_Hostile::
	lock
	faceplayer
	msgbox Wasteland_Port_Text_Hostile, MSGBOX_DEFAULT
	release
	end

Wasteland_Port_Text_Hostile::
	.string "That deployment man, the one who\n"
	.string "flipped the switch. If I ever met\l"
	.string "his family, I'd have a few words.\l"
	.string "His kid lives in some big house\l"
	.string "up north, safe as anything.$"

Wasteland_Port_EventScript_Cook::
	lock
	faceplayer
	msgbox Wasteland_Port_Text_Cook, MSGBOX_DEFAULT
	release
	end

Wasteland_Port_Text_Cook::
	.string "Best fish stew in the port. Pays\n"
	.string "a fee to the wardens, a tax to\l"
	.string "the Harbormaster, and a tip to\l"
	.string "the ghost of whoever ate here\l"
	.string "last. Sit.$"

Wasteland_Port_EventScript_Debt::
	lock
	faceplayer
	msgbox Wasteland_Port_Text_Debt, MSGBOX_DEFAULT
	release
	end

Wasteland_Port_Text_Debt::
	.string "That deployment man? He fixed our\n"
	.string "pump after the signal. Only time\l"
	.string "anyone from the company did a\l"
	.string "thing for us. Don't say that too\l"
	.string "loud here.$"

Wasteland_Port_EventScript_Mother::
	lock
	faceplayer
	msgbox Wasteland_Port_Text_Mother, MSGBOX_DEFAULT
	release
	end

Wasteland_Port_Text_Mother::
	.string "My mother's on the register. Page\n"
	.string "nine. I check it every week in\l"
	.string "case someone updates it.$"

Wasteland_Port_EventScript_Ships::
	lock
	faceplayer
	msgbox Wasteland_Port_Text_Ships, MSGBOX_DEFAULT
	release
	end

Wasteland_Port_Text_Ships::
	.string "Ships used to come and go. Now\n"
	.string "one ship comes and goes, and it\l"
	.string "doesn't take passengers.$"

Wasteland_Port_EventScript_Warm::
	lock
	faceplayer
	msgbox Wasteland_Port_Text_Warm, MSGBOX_DEFAULT
	release
	end

Wasteland_Port_Text_Warm::
	.string "Some people sleep at the\n"
	.string "shipyard. It's warmer. And nobody\l"
	.string "from the trucks goes there.$"

Wasteland_Port_EventScript_OwnList::
	lock
	faceplayer
	msgbox Wasteland_Port_Text_OwnList, MSGBOX_DEFAULT
	release
	end

Wasteland_Port_Text_OwnList::
	.string "I keep my own list. Better than\n"
	.string "the Harbormaster's. Hers only\l"
	.string "counts the ones who were\l"
	.string "registered. Mine counts the rest.$"

Wasteland_Port_EventScript_Complaint::
	lock
	faceplayer
	msgbox Wasteland_Port_Text_Complaint, MSGBOX_DEFAULT
	release
	end

Wasteland_Port_Text_Complaint::
	.string "I filed a complaint about the\n"
	.string "complaints office. It was\l"
	.string "accepted. I'm still waiting for\l"
	.string "the acknowledgment of the\l"
	.string "acceptance.$"

Wasteland_Port_EventScript_Guard::
	lock
	faceplayer
	msgbox Wasteland_Port_Text_Guard, MSGBOX_DEFAULT
	release
	end

Wasteland_Port_Text_Guard::
	.string "Hall's closed to unregistered\n"
	.string "visitors. The Registrar's the\l"
	.string "house on the west side. Name,\l"
	.string "origin, purpose. Don't overthink\l"
	.string "it.$"

Wasteland_Port_EventScript_RegistrarSign::
	msgbox Wasteland_Port_Text_RegistrarSign, MSGBOX_SIGN
	end

Wasteland_Port_Text_RegistrarSign::
	.string "REGISTRAR. All arrivals. Free,\n"
	.string "mandatory, and binding.$"

Wasteland_Port_EventScript_HallSign::
	msgbox Wasteland_Port_Text_HallSign, MSGBOX_SIGN
	end

Wasteland_Port_Text_HallSign::
	.string "THE HARBORMASTER'S HALL.\n"
	.string "Appointments by registration\l"
	.string "only.$"

Wasteland_Port_EventScript_PortSign::
	msgbox Wasteland_Port_Text_PortSign, MSGBOX_SIGN
	end

Wasteland_Port_Text_PortSign::
	.string "THE PORT. Every crate counted.\n"
	.string "Every crossing noted. Every name\l"
	.string "kept.$"

