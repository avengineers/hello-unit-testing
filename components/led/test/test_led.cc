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

MATCHER_P(LEDBrightnessEq, expected, "")
{
    return (arg.brightness == expected.brightness);
}

TEST(LEDTest, FullBrightness)
{
    /* Arrange */
    CREATE_MOCK(myMock);
    EXPECT_CALL(myMock, setLEDBrightness(LEDBrightnessEq(half_brightness))).Times(1);

    /* Act */
    setBrightness(FULL);

    /* Assert */
}
