#ifndef POSITION_CONTROLLER_H
#define POSITION_CONTROLLER_H

#include <stdint.h>

typedef struct
{
    uint16_t x;
    uint16_t y;
} Position;

/* Set new position */
void setNewPostion(Position* position);

/* Get current position */
Position getCurrentPosition(void);

#endif /* POSITION_CONTROLLER_H */
