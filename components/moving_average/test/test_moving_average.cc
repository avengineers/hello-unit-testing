#include <gtest/gtest.h>
using namespace testing;

extern "C"
{
#include "moving_average.h"
}

TEST(MovingAverageTest, GetAveragedValue)
{
    /* Arrange */

    /* Act */
    getAveragedValue();

    /* Assert */
    EXPECT_TRUE(false);
}
