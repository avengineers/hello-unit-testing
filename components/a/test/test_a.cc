#include <gtest/gtest.h>
using namespace testing;

extern "C"
{
#include "a.h"
#include "b.h"
}

// Define a struct to hold the parameters for testing component a
struct ComponentAParameters
{
    const char *description;
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

    /* Act */
    a();

    /* Assert */
}

// Instantiate the test suite with a set of parameters
INSTANTIATE_TEST_SUITE_P(
    CompATests,
    CompATest,
    ::testing::Values(
        ComponentAParameters{"Test 1"}));
