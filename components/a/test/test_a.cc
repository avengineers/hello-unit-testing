#include <gtest/gtest.h>
using namespace testing;

extern "C"
{
#include "a.h"
#include "b.h"
}

#include "mockup_components_a.h"

TEST(CompATest, FunctionA_1)
{
    /* Arrange */
    CREATE_MOCK(myMock);
    ON_CALL(myMock, getB1()).WillByDefault(Return(7));
    ON_CALL(myMock, getB2()).WillByDefault(Return(5));


    /* Act */
    int32_t returnValueA = a();

    /* Assert */
    EXPECT_EQ(returnValueA, 13);
}

TEST(CompATest, FunctionA_2)
{
    /* Arrange */
    CREATE_MOCK(myMock);
    ON_CALL(myMock, getB1()).WillByDefault(Return(38));
    ON_CALL(myMock, getB2()).WillByDefault(Return(-142));

    /* Act */
    int32_t returnValueA = a();

    /* Assert */
    EXPECT_EQ(returnValueA, -103);
}

TEST(CompATest, FunctionA_3)
{
    /* Arrange */
    CREATE_MOCK(myMock);
    ON_CALL(myMock, getB1()).WillByDefault(Return(-322));
    ON_CALL(myMock, getB2()).WillByDefault(Return(-338));

    /* Act */
    int32_t returnValueA = a();

    /* Assert */
    EXPECT_EQ(returnValueA, -659);
}
