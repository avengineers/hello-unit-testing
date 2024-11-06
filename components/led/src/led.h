#ifndef LED_H
#define LED_H

typedef enum
{
    RED,
    GREEN,
    BLUE
} Color;

typedef enum
{
    OFF,
    HALF,
    FULL
} Brightness;

/* Set LED color */
extern void setColor(Color color);

/* Set LED brightness */
extern void setBrightness(Brightness brightness);

#endif /* LED_H */
