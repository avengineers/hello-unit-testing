#ifndef DIAGNOSTIC_H
#define DIAGNOSTIC_H

#include <stdbool.h>

typedef enum
{
    HIGH_BEAM_DTC,
    LOW_BEAM_DTC
} BeamTypeDTC;

/* Initialization */
extern void diagnosticInit(void);

/* Check if DTC is set */
extern bool isDTCSet(BeamTypeDTC dtc);

/* Diagnostic cyclic function */
extern void diagnosticCyclic(void);

#endif /* DIAGNOSTIC_H */
