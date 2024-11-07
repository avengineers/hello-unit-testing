#include <gtest/gtest.h>
using namespace testing;

extern "C"
{
#include "led.h"
}

#include "mockup_components_led.h"

const LEDBrightness full_brightness = { 100U };
const LEDBrightness half_brightness = { 50U };
const LEDBrightness led_off = { 0U };

const LEDColor red = { 0xFFU, 0U, 0U };
const LEDColor green = { 0U, 0xFFU, 0U };
const LEDColor blue = { 0U, 0U, 0xFFU };

MATCHER_P(LEDBrightnessEq, expected, "")
{
    return (arg.brightness == expected.brightness);
}

MATCHER_P(LEDColorEq, expected, "")
{
    return ((arg.red == expected.red) &&
        (arg.green == expected.green) &&
        (arg.blue == arg.blue));
}

TEST(LEDTest, FullBrightness)
{
    /* Arrange */
    CREATE_MOCK(myMock);
    EXPECT_CALL(myMock, setLEDBrightness(LEDBrightnessEq(full_brightness))).Times(1);

    /* Act */
    setBrightness(FULL);

    /* Assert */
}

TEST(LEDTest, HalfBrightness)
{
    /* Arrange */
    CREATE_MOCK(myMock);
    EXPECT_CALL(myMock, setLEDBrightness(LEDBrightnessEq(half_brightness))).Times(1);

    /* Act */
    setBrightness(HALF);

    /* Assert */
}

TEST(LEDTest, LEDOff)
{
    /* Arrange */
    CREATE_MOCK(myMock);
    EXPECT_CALL(myMock, setLEDBrightness(LEDBrightnessEq(led_off))).Times(1);

    /* Act */
    setBrightness(OFF);

    /* Assert */
}

TEST(LEDTest, RedColor)
{
    /* Arrange */
    CREATE_MOCK(myMock);
    EXPECT_CALL(myMock, setLEDColor(LEDColorEq(red))).Times(1);

    /* Act */
    setColor(RED);

    /* Assert */
}

TEST(LEDTest, GreenColor)
{
    /* Arrange */
    CREATE_MOCK(myMock);
    EXPECT_CALL(myMock, setLEDColor(LEDColorEq(green))).Times(1);

    /* Act */
    setColor(GREEN);

    /* Assert */
}

TEST(LEDTest, BlueColor)
{
    /* Arrange */
    CREATE_MOCK(myMock);
    EXPECT_CALL(myMock, setLEDColor(LEDColorEq(blue))).Times(1);

    /* Act */
    setColor(BLUE);

    /* Assert */
}
