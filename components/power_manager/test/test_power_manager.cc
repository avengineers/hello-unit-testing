#include <gtest/gtest.h>
using namespace testing;

extern "C"
{
#include"power_manager.h"
}

TEST(PowerManagerTest, FailingTest)
{
    /* Arrange */

    /* Act */
    PowerManagerState current_state = getCurrentState();

    /* Assert */
    EXPECT_EQ(current_state, PREPARE_SHUTDOWN);
}
