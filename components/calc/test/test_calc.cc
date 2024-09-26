#include <gtest/gtest.h>
using namespace testing;

extern "C"
{
#include "calc.h"
}

TEST(CalcTest, Add)
{
    EXPECT_EQ(calc_add(10, 20), 30);
    EXPECT_EQ(calc_add(10, -20), -10);
    EXPECT_EQ(calc_add(-10, -20), -30);
    EXPECT_EQ(calc_add(INT16_MAX, 1), INT16_MAX + 1);
    EXPECT_EQ(calc_add(INT16_MIN, -1), INT16_MIN - 1);
}
