#ifndef POSITION_MANAGER_H
#define POSITION_MANAGER_H

#include <stdint.h>

typedef enum
{
    MOVE_OK,            /* Position is correct, movement in the range*/
    MOVE_NOT_POSSIBLE,  /* Position is correct, movement not in the range*/
    POSITION_WRONG      /* Position is not correct */
} MovementStatus;

typedef enum
{
    MOVE_LEFT,
    MOVE_RIGHT,
    MOVE_UP,
    MOVE_DOWN
} MovementDirection;

/* Movement commands */
extern MovementStatus move(uint16_t points, MovementDirection direction);

#endif /* POSITION_MANAGER_H */
