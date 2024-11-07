#include "voltage_monitor.h"
#include "voltage_adc.h"

#define VOLTAGE_MAX 16000   /* Maximal measured voltage */
#define ADC_MAX     0x3FFU  /* Maximal ADC value */
#define V_LOW       10000U
#define V_HIGH      14000U

static uint16_t current_voltage = 0U;
static VoltageStatus voltage_status = NOT_VALID;

/* Voltage monitor initialization */
void voltageMonitorInit(void)
{
    current_voltage = 0U;
    voltage_status = NOT_VALID;
}

/* Get the voltage value and status */
VoltageStatus getVoltage(uint16_t* voltage)
{
    *voltage = current_voltage;

    return voltage_status;
}

/* Voltage converter cyclic function */
void voltageMonitorCyclic(void)
{
    uint16_t adc_value = 0U;
    ADCReturnType result = getADCValue(&adc_value);

    if (result == ADC_READ_OK)
    {
        /*Convert ADC value */
        current_voltage = (uint16_t)(((uint32_t)adc_value * VOLTAGE_MAX) / ADC_MAX);

        if (current_voltage < V_LOW)
        {
            voltage_status = LOW_VOLTAGE;
        }
        else if (current_voltage > V_HIGH)
        {
            voltage_status = HIGH_VOLTAGE;
        }
        else
        {
            voltage_status = NORMAL_VOLTAGE;
        }
    }
    else
    {
        voltage_status = NOT_VALID;
    }
}
