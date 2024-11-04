#include <gtest/gtest.h>
using namespace testing;

extern "C"
{
#include "a.h"
#include "b.h"
}

TEST(CompATest, FunctionA)
{
    /* Arrange */

    /* Act */
    a();

    /* Assert */
    EXPECT_TRUE(false)
}
