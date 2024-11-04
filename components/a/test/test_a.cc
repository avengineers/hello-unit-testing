#include <gtest/gtest.h>
using namespace testing;

extern "C"
{
#include "a.h"
#include "b.h"

    int16_t FUNC_GETB1_RETURN_VALUE = 0;
    int16_t FUNC_GETB2_RETURN_VALUE = 0;

    int16_t getB1()
    {
        return FUNC_GETB1_RETURN_VALUE;
    }

    int16_t getB2()
    {
        return FUNC_GETB2_RETURN_VALUE;
    }
}

TEST(CompATest, FunctionA_1)
{
    /* Arrange */
    FUNC_GETB1_RETURN_VALUE = 7;
    FUNC_GETB2_RETURN_VALUE = 5;

    /* Act */
    int32_t returnValueA = a();

    /* Assert */
    EXPECT_EQ(returnValueA, 13);
}

TEST(CompATest, FunctionA_2)
{
    /* Arrange */
    FUNC_GETB1_RETURN_VALUE = 38;
    FUNC_GETB2_RETURN_VALUE = -142;

    /* Act */
    int32_t returnValueA = a();

    /* Assert */
    EXPECT_EQ(returnValueA, -103);
}

TEST(CompATest, FunctionA_3)
{
    /* Arrange */
    FUNC_GETB1_RETURN_VALUE = -322;
    FUNC_GETB2_RETURN_VALUE = -338;

    /* Act */
    int32_t returnValueA = a();

    /* Assert */
    EXPECT_EQ(returnValueA, -659);
}
