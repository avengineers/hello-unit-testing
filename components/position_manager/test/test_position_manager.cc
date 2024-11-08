#include <gtest/gtest.h>
using namespace testing;

extern "C"
{
#include "position_manager.h"
}

#define MOVEMENT_IN_RANGE_FOR_MIDDLE        500U
#define MOVEMENT_OUT_OF_RANGE_FOR_MIDDLE    501U
#define MAX_X                              1000U
#define MAX_Y                              1000U

TEST(PositionManagerTest, MoveLeftInRange)
{
    /* Arrange */

    /* Act */
    MovementStatus status = moveLeft(MOVEMENT_IN_RANGE_FOR_MIDDLE);

    /* Assert */
    EXPECT_EQ(status, MOVE_OK);
}
