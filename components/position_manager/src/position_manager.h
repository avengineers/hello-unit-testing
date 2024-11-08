#ifndef POSITION_MANAGER_H
#define POSITION_MANAGER_H

#include <stdint.h>

typedef enum
{
    MOVE_OK,            /* Position is correct, movement in the range*/
    MOVE_NOT_POSSIBLE,  /* Position is correct, movement not in the range*/
    POSITION_WRONG      /* Position is not correct */
} MovementStatus;

/* Movement commands */
extern MovementStatus moveLeft(uint16_t points);
extern MovementStatus moveRight(uint16_t points);
extern MovementStatus moveUp(uint16_t points);
extern MovementStatus moveDown(uint16_t points);

#endif /* POSITION_MANAGER_H */
