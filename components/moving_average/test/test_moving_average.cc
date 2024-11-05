#include <gtest/gtest.h>
using namespace testing;

extern "C"
{
#include "moving_average.h"
}

class MovingAverageTest : public Test
{
protected:
    void SetUp(void) override
    {
        movingAverageInit();
    }
};

TEST_F(MovingAverageTest, Initialization)
{
    /* Arrange */

    /* Act */
    int16_t returnAveragedValue = getAveragedValue();

    /* Assert */
    EXPECT_EQ(returnAveragedValue, 0);
}

TEST_F(MovingAverageTest, AddSingleValue)
{
    /* Arrange */
    addNewValue(10);

    /* Act */
    int16_t returnAveragedValue = getAveragedValue();

    /* Assert */
    EXPECT_EQ(returnAveragedValue, 10);
}

TEST_F(MovingAverageTest, AddMultipleValues)
{
    /* Arrange */
    addNewValue(10);
    addNewValue(20);
    addNewValue(30);

    /* Act */
    int16_t returnAveragedValue = getAveragedValue();

    /* Assert */
    EXPECT_EQ(returnAveragedValue, 20);
}

TEST_F(MovingAverageTest, FullWindow)
{
    /* Arrange */
    addNewValue(10);
    addNewValue(20);
    addNewValue(30);
    addNewValue(40);

    /* Act */
    int16_t returnAveragedValue = getAveragedValue();

    /* Assert */
    EXPECT_EQ(returnAveragedValue, 25);
}

TEST_F(MovingAverageTest, WindowOverflow)
{
    /* Arrange */
    addNewValue(10);
    addNewValue(20);
    addNewValue(30);
    addNewValue(40);
    addNewValue(50);
    addNewValue(80);

    /* Act */
    int16_t returnAveragedValue = getAveragedValue();

    /* Assert */
    EXPECT_EQ(returnAveragedValue, 50);
}
