#include <gtest/gtest.h>
using namespace testing;

extern "C"
{
#include "calc.h"
}

TEST(CalcTest, add_two_positive_numbers)
{
    EXPECT_EQ(calc_add(10, 20), 30);
}

TEST(CalcTest, add_positive_and_negative_numbers)
{
    EXPECT_EQ(calc_add(10, -20), -10);
}

TEST(CalcTest, add_two_negative_numbers)
{
    EXPECT_EQ(calc_add(-10, -20), -30);
}

TEST(CalcTest, add_positive_number_and_max_int16)
{
    EXPECT_EQ(calc_add(INT16_MAX, 1), INT16_MAX + 1);
}

TEST(CalcTest, add_negative_number_and_min_int16)
{
    EXPECT_EQ(calc_add(INT16_MIN, -1), INT16_MIN - 1);
}

TEST(CalcTest, add_two_max_int16)
{
    EXPECT_EQ(calc_add(INT16_MAX, INT16_MAX), INT16_MAX + INT16_MAX);
}

TEST(CalcTest, add_two_min_int16)
{
    EXPECT_EQ(calc_add(INT16_MIN, INT16_MIN), INT16_MIN + INT16_MIN);
}

TEST(CalcTest, add_max_int16_and_min_int16)
{
    EXPECT_EQ(calc_add(INT16_MAX, INT16_MIN), INT16_MAX + INT16_MIN);
}
