#include <gtest/gtest.h>
using namespace testing;

extern "C"
{
#include "voltage_monitor.h"
}

TEST(VoltageMonitorTest, FailingTest)
{
    /* Arrange */

    /* Act */

    /* Assert */
    EXPECT_TRUE(false);
}
