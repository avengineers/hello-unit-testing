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
// Define a struct to hold the parameters for testing component a
struct ComponentAParameters
{
    const char *description;
    int16_t funcGetB1ReturnValue;
    int16_t funcGetB2ReturnValue;
    int32_t expectedResult;
};

// Override the cout operator for TestParam so that it can be printed in the test output
std::ostream &operator<<(std::ostream &os, const ComponentAParameters &param)
{
    os << param.description;
    return os;
}

// Define a test fixture class
class CompATest : public ::testing::TestWithParam<struct ComponentAParameters>
{
};

TEST_P(CompATest, FunctionA)
{
    /* Arrange */
    ComponentAParameters param = GetParam();

    FUNC_GETB1_RETURN_VALUE = param.funcGetB1ReturnValue;
    FUNC_GETB2_RETURN_VALUE = param.funcGetB2ReturnValue;

    /* Act */
    int32_t returnValueA = a();

    /* Assert */
    EXPECT_EQ(returnValueA, param.expectedResult);
}

// Instantiate the test suite with a set of parameters
INSTANTIATE_TEST_SUITE_P(
    CompATests,
    CompATest,
    ::testing::Values(
        ComponentAParameters{"Test 1", 7, 5, 13},
        ComponentAParameters{"Test 2", 38, -142, -103},
        ComponentAParameters{"Test 3", -322, -338, -659}));
