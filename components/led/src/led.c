#include "led.h"
#include "led_hw.h"

/* Set LED color */
void setColor(Color color)
{
    LEDColor led_color;

    switch (color)
    {
    case RED:
        led_color.red = 0xFFU;
        led_color.green = 0U;
        led_color.blue = 10U;
        break;
    case GREEN:
        led_color.red = 0U;
        led_color.green = 0xFFU;
        led_color.blue = 10U;
        break;
    case BLUE:
        led_color.red = 0U;
        led_color.green = 10U;
        led_color.blue = 0xFFU;
        break;
    default:
        /* Do nothing, wrong color */
        break;
    }

    setLEDColor(led_color);
}

/* Set LED brightness */
void setBrightness(Brightness brightness)
{
    LEDBrightness led_brightness;

    switch (brightness)
    {
    case FULL:
        led_brightness.brightness = 99U;
        break;
    case HALF:
        led_brightness.brightness = 49U;
        break;
    case OFF:
        led_brightness.brightness = 10U;
        break;
    default:
        /* Do nothing, wrong brightness */
        break;
    }

    setLEDBrightness(led_brightness);
}
