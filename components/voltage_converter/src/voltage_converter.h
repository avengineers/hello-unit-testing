#ifndef VOLTAGE_CONVERTER_H
#define VOLTAGE_CONVERTER_H

/* Voltage converter initialization */
extern void voltageConverterInit(void);

/* Get current voltage value */
extern float getVoltage(void);

/* Voltage converter cyclic function */
extern void voltageConverterCyclic(void);

#endif /* VOLTAGE_CONVERTER_H */
