#include <gtest/gtest.h>
using namespace testing;

extern "C"
{
#include "calc.h"
}

// Define a struct to hold the parameters for testing calc_add()
struct CalcAddParameters
{
    const char* description;
    int16_t a;
    int16_t b;
    int32_t expected;
};

// Override the cout operator for TestParam so that it can be printed in the test output
std::ostream& operator<<(std::ostream& os, const CalcAddParameters& param)
{
    os << param.description;
    return os;
}

// Define a test fixture class
class CalcTest : public ::testing::TestWithParam<struct CalcAddParameters>
{
};

TEST_P(CalcTest, Add)
{
    // Arrange
    CalcAddParameters param = GetParam();

    // Act and Assert
    EXPECT_EQ(calc_add(param.a, param.b), param.expected) << "Test case: " << param.description;
}

// Instantiate the test suite with a set of parameters
INSTANTIATE_TEST_SUITE_P(
    CalcTests,
    CalcTest,
    ::testing::Values(
        CalcAddParameters{ "Add 0 and 0", 0, 0, 0 },
        CalcAddParameters{ "Add two positive values", 10, 20, 30 },
        CalcAddParameters{ "Add a positive and a negative value", 10, -20, -10 },
        CalcAddParameters{ "Add two negative values", -10, -20, -30 },
        CalcAddParameters{ "Add maximum and 1", INT16_MAX, 1, INT16_MAX + 1 },
        CalcAddParameters{ "Add minimum and -1", INT16_MIN, -1, INT16_MIN - 1 },
        CalcAddParameters{ "Add maximum and maximum", INT16_MAX, INT16_MAX, INT16_MAX * 2 },
        CalcAddParameters{ "Add minimum and minimum", INT16_MIN, INT16_MIN, INT16_MIN * 2 }));
