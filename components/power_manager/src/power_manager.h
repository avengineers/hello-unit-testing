#ifndef POWER_MANAGER
#define POWER_MANAGER

typedef enum
{
    INITIALISATION,
    ACTIVE,
    IDLE,
    LOW_POWER,
    PREPARE_SHUTDOWN
} PowerManagerState;

/* Power manager initialization */
extern void PowerManagerInit(void);

/* Get current power manager state */
extern PowerManagerState getCurrentState(void);

/* Initiate shut down sequence */
void shutDown(void);

/* Power manager cyclic function */
extern void powerManagerCyclic(void);

#endif /* POWER_MANAGER */
