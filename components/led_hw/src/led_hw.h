#ifndef LED_HW_H
#define LED_HW_H

#include <stdint.h>

typedef struct
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} LEDColor;

typedef struct
{
    uint8_t brightness;
} LEDBrightness;


/* Set LED color */
extern void setLEDColor(LEDColor color);

/* Set LED brightness */
extern void setLEDBrightness(LEDBrightness brightness);

#endif /* LED_HW_H */
