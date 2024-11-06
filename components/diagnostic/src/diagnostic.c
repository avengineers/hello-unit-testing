#include "diagnostic.h"
#include "headlights.h"

#include<stdint.h>

#define MAX_DEBOUNCE  2U

static bool low_beam_dtc_status = false;
static bool high_beam_dtc_status = false;
static uint8_t low_beam_dtc_debounce = 0U;
static uint8_t high_beam_dtc_debounce = 0U;

/* Initialization */
void diagnosticInit(void)
{
    low_beam_dtc_status = false;
    high_beam_dtc_status = false;

    low_beam_dtc_debounce = 0U;
    high_beam_dtc_debounce = 0U;
}

/* Check if DTC is set */
bool isDTCSet(BeamTypeDTC dtc)
{
    bool dtc_status = false;

    switch (dtc)
    {
    case HIGH_BEAM_DTC:
        dtc_status = high_beam_dtc_status;
        break;
    case LOW_BEAM_DTC:
        dtc_status = low_beam_dtc_status;
        break;
    default:
        /* Unknown DTC, return false */
        break;
    }

    return dtc_status;
}

/* Diagnostic cyclic function */
void diagnosticCyclic(void)
{
    TestStatus low_beam_test_status = runDiagnosticTest(LOW_BEAM);
    TestStatus high_beam_test_status = runDiagnosticTest(HIGH_BEAM);

    if ((low_beam_test_status == TEST_FAILED) && (low_beam_dtc_debounce < MAX_DEBOUNCE))
    {
        low_beam_dtc_debounce++;
    }
    else if (low_beam_test_status == TEST_PASSED)
    {
        low_beam_dtc_debounce = 0U;
    }
    else
    {
        /* Nothing to do, MISRA */
    }

    if ((high_beam_test_status == TEST_FAILED) && (high_beam_dtc_debounce < MAX_DEBOUNCE))
    {
        high_beam_dtc_debounce++;
    }
    else if (high_beam_test_status == TEST_PASSED)
    {
        high_beam_dtc_debounce = 0U;
    }
    else
    {
        /* Nothing to do, MISRA */
    }

    if (low_beam_dtc_debounce == MAX_DEBOUNCE)
    {
        low_beam_dtc_status = true;
    }
    else
    {
        low_beam_dtc_status = false;
    }

    if (high_beam_dtc_debounce == MAX_DEBOUNCE)
    {
        high_beam_dtc_status = true;
    }
    else
    {
        high_beam_dtc_status = false;
    }
}
