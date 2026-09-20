#include "global.h"
#include "event_data.h"
#include "battle_setup.h"
#include "constants/opponents.h"
#include "test/test.h"

// Wasteland: trainer ids above the standard flag range (>= 864) are tracked in a spare flag block
// (TRAINER_FLAG_ID in constants/flags.h) so the save layout never has to change.

// The save layout depends on these staying put: if this fails, existing saves are broken.
STATIC_ASSERT(SYSTEM_FLAGS == 0x860, WastelandSystemFlagsMoved);
STATIC_ASSERT(FLAG_BADGE01_GET == 0x867, WastelandBadgeFlagMoved);
STATIC_ASSERT(WASTELAND_EXTRA_TRAINER_FLAGS_START + WASTELAND_EXTRA_TRAINER_FLAGS_COUNT <= TRAINER_FLAGS_START, WastelandExtraTrainerFlagsOverlap);
STATIC_ASSERT(MAX_TRAINERS_COUNT <= WASTELAND_TRAINER_FLAG_SPLIT + WASTELAND_EXTRA_TRAINER_FLAGS_COUNT, WastelandTrainerCountExceedsFlagSpace);

TEST("(Wasteland) Standard-range and extended-range trainer flags set independently")
{
    FlagClear(TRAINER_FLAG_ID(TRAINER_HAVERBROOK_PROTECTOR));
    FlagClear(TRAINER_FLAG_ID(864));
    FlagClear(TRAINER_FLAG_ID(MAX_TRAINERS_COUNT - 1));

    EXPECT_EQ(HasTrainerBeenFought(TRAINER_HAVERBROOK_PROTECTOR), FALSE);
    EXPECT_EQ(HasTrainerBeenFought(864), FALSE);
    EXPECT_EQ(HasTrainerBeenFought(MAX_TRAINERS_COUNT - 1), FALSE);

    SetTrainerFlag(864);
    EXPECT_EQ(HasTrainerBeenFought(864), TRUE);
    EXPECT_EQ(HasTrainerBeenFought(TRAINER_HAVERBROOK_PROTECTOR), FALSE);
    EXPECT_EQ(HasTrainerBeenFought(865), FALSE);

    SetTrainerFlag(MAX_TRAINERS_COUNT - 1);
    EXPECT_EQ(HasTrainerBeenFought(MAX_TRAINERS_COUNT - 1), TRUE);

    SetTrainerFlag(TRAINER_HAVERBROOK_PROTECTOR);
    EXPECT_EQ(HasTrainerBeenFought(TRAINER_HAVERBROOK_PROTECTOR), TRUE);
    EXPECT_EQ(FlagGet(TRAINER_FLAGS_START + TRAINER_HAVERBROOK_PROTECTOR), TRUE);

    ClearTrainerFlag(864);
    EXPECT_EQ(HasTrainerBeenFought(864), FALSE);
    EXPECT_EQ(HasTrainerBeenFought(MAX_TRAINERS_COUNT - 1), TRUE);
}

TEST("(Wasteland) Extended trainer flag range does not touch any flag outside its block")
{
    // The flag just below and just above the extended block must be untouched.
    FlagClear(WASTELAND_EXTRA_TRAINER_FLAGS_START - 1);
    FlagClear(WASTELAND_EXTRA_TRAINER_FLAGS_START + WASTELAND_EXTRA_TRAINER_FLAGS_COUNT);
    SetTrainerFlag(WASTELAND_TRAINER_FLAG_SPLIT);
    SetTrainerFlag(MAX_TRAINERS_COUNT - 1);
    EXPECT_EQ(FlagGet(WASTELAND_EXTRA_TRAINER_FLAGS_START - 1), FALSE);
    EXPECT_EQ(FlagGet(WASTELAND_EXTRA_TRAINER_FLAGS_START + WASTELAND_EXTRA_TRAINER_FLAGS_COUNT), FALSE);
}
