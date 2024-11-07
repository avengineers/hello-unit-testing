#ifndef VOLTAGE_MONITOR
#define VOLTAGE_MONITOR

#include <stdint.h>

typedef enum
{
    NOT_VALID,
    LOW_VOLTAGE,
    HIGH_VOLTAGE,
    NORMAL_VOLTAGE
} VoltageStatus;

/* Voltage monitor initialization */
extern void voltageMonitorInit(void);

/* Get the voltage value and status */
extern VoltageStatus getVoltage(uint16_t* voltage);

/* Voltage monitor cyclic function */
extern void voltageMonitorCyclic(void);

#endif /* VOLTAGE_MONITOR */
