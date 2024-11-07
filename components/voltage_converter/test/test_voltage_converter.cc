#include <gtest/gtest.h>
using namespace testing;

extern "C"
{
#include "voltage_converter.h"
}

TEST(VoltageConverterTest, FailingTest)
{
    /* Arrange */

    /* Act */
    float voltage = getVoltage();

    /* Assert */
    EXPECT_TRUE(false);
}
