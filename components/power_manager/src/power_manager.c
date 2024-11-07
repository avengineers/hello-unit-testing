#include "power_manager.h"

#include "voltage_adc.h"
#include "network.h"

#include <stdbool.h>

/* To avoid conversion, raw data will be used: 6V = 0x17FU*/
#define ADC_MIN_VOLTAGE   0x17FU

static PowerManagerState currentState = INITIALISATION;
static bool shut_down = false;

/* Internal functions */
static bool isVoltageBelowThreshold(void);
static void handleInitializationState(void);
static void handleActiveState(void);
static void handleIdleState(void);
static void handlePrepareShutdownState(void);

/* Power manager initialization */
void PowerManagerInit(void)
{
    currentState = INITIALISATION;
    shut_down = false;
}

/* Initiate shut down sequence */
void shutDown(void)
{
    shut_down = true;
}

/* Get current power manager state */
PowerManagerState getCurrentState(void)
{
    return currentState;
}

/* Power manager cyclic function */
void powerManagerCyclic(void)
{
    if (isVoltageBelowThreshold())
    {
        currentState = PREPARE_SHUTDOWN;
    }
    else if (currentState == INITIALISATION)
    {
        handleInitializationState();
    }
    else if (currentState == ACTIVE)
    {
        handleActiveState();
    }
    else if (currentState == IDLE)
    {
        handleIdleState();
    }
    else
    {
        handlePrepareShutdownState();
    }
}

static bool isVoltageBelowThreshold(void)
{
    uint16_t voltage = 0U;
    bool is_voltage_below_threshold = true;

    if (getADCValue(&voltage) == ADC_READ_NOK)
    {
        voltage = 0U;
    }

    if (voltage >= ADC_MIN_VOLTAGE)
    {
        is_voltage_below_threshold = false;
    }

    return is_voltage_below_threshold;
}


static void handleInitializationState(void)
{
    NetworkControllerStatus network_status = getNetworkControllerStatus();

    if (isVoltageBelowThreshold() || (network_status == NETWORK_UNINITIALIZED))
    {
        currentState = PREPARE_SHUTDOWN;
    }
    else if (network_status == NETWORK_INITIALIZED)
    {
        currentState = ACTIVE;
    }
    else
    {
        /* Nothing to do, MISRA */
    }
}

static void handleActiveState(void)
{
    if (getCommunicationStatus() == NO_COMMUNICATION)
    {
        currentState = IDLE;
    }
    else if (isVoltageBelowThreshold() || shut_down)
    {
        currentState = PREPARE_SHUTDOWN;
    }
    else
    {
        /* Nothing to do, MISRA */
    }
}

static void handleIdleState(void)
{
    if (getCommunicationStatus() == FULL_COMMUNICATION)
    {
        currentState = ACTIVE;
    }
    else if (isVoltageBelowThreshold() || shut_down)
    {
        currentState = PREPARE_SHUTDOWN;
    }
    else
    {
        /* Nothing to do, MISRA */
    }
}

static void handlePrepareShutdownState(void)
{
    /* System is ready for shutdown */
}
