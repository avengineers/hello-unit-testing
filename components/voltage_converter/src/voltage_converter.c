#include "voltage_converter.h"
#include "voltage_adc.h"

#define VOLTAGE_MAX 16.0f   /* Maximal measured voltage */
#define ADC_MAX     4095.0f /* Maximal ADC value */

static float voltage = 0.0f;

/* Voltage converter initialization */
extern void voltageConverterInit(void)
{
    voltage = 0.0f;
}

/* Get current voltage value */
extern float getVoltage(void)
{
    return voltage;
}

/* Voltage converter cyclic function */
extern void voltageConverterCyclic(void)
{
    uint16_t adc_value = 0U;
    ADCReturnType result = getADCValue(&adc_value);

    if (result == ADC_READ_OK)
    {
        /*Convert ADC value */
        voltage = (adc_value * VOLTAGE_MAX);
    }
}
