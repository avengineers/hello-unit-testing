#include <gtest/gtest.h>
using namespace testing;

extern "C"
{
#include "diagnostic.h"
}

TEST(DiagnosticTest, FailingTest)
{
    /* Arrange */

    /* Act */
    diagnosticCyclic();

    /* Assert */
    EXPECT_TRUE(false);
}
