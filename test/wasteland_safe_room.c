#include "global.h"
#include "event_data.h"
#include "constants/battle.h"
#include "test/overworld_script.h"
#include "test/test.h"

// Wasteland: covers the state-changing logic used by
// Wasteland_SafeRoom_EventScript_Dad (data/maps/Wasteland_SafeRoom/scripts.inc).
// The overworld itself (lock/faceplayer/msgbox/release, walking up to the NPC)
// isn't available in the headless test runner (see test/overworld_script.h), so
// this only exercises the givemon + flag bookkeeping the real script performs.

TEST("(Wasteland) Safe room gift gives the player Houndour (Alder) and sets the received/Pokemon-menu flags")
{
    ZeroPlayerPartyMons();
    EXPECT_EQ(FlagGet(FLAG_RECEIVED_WASTELAND_STARTER), FALSE);

    RUN_OVERWORLD_SCRIPT(
        givemon SPECIES_HOUNDOUR_ALDER, 5;
        setflag FLAG_RECEIVED_WASTELAND_STARTER;
        setflag FLAG_SYS_POKEMON_GET;
    );

    EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_SPECIES), SPECIES_HOUNDOUR_ALDER);
    EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_LEVEL), 5);
    EXPECT_EQ(FlagGet(FLAG_RECEIVED_WASTELAND_STARTER), TRUE);
    EXPECT_EQ(FlagGet(FLAG_SYS_POKEMON_GET), TRUE);
}
