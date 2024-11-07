#ifndef VOLTAGE_ADC_H
#define VOLTAGE_ADC_H

#include <stdint.h>

typedef enum
{
    ADC_READ_OK,
    ADC_READ_NOK
} ADCReturnType;

/* ADC value */
extern ADCReturnType getADCValue(uint16_t* value);

#endif /* ADC_H */
