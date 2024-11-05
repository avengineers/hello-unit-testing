#ifndef MOVING_AVERAGE_H
#define MOVING_AVERAGE_H

#include <stdint.h>

/* Initialization */
extern void movingAverageInit(void);

/* Add new value to average calculation */
extern void addNewValue(uint16_t new_value);

/* Get averaged value */
extern int16_t getAveragedValue(void);

#endif /* MOVING_AVERAGE_H */
