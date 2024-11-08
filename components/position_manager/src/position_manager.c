#include "position_manager.h"

#include "position_controller.h"

#define MAX_X   1000U
#define MAX_Y   1000U

MovementStatus moveLeft(uint16_t points)
{
    Position position = getCurrentPosition();
    MovementStatus return_status = MOVE_NOT_POSSIBLE;

    if ((position.x <= MAX_X) && (position.y <= MAX_Y))
    {
        if (position.x >= points)
        {
            position.x -= points;
            return_status = MOVE_OK;

            setNewPostion(&position);
        }
    }
    else
    {
        return_status = POSITION_WRONG;
    }

    return return_status;
}

MovementStatus moveRight(uint16_t points)
{
    Position position = getCurrentPosition();
    MovementStatus return_status = MOVE_NOT_POSSIBLE;

    if ((position.x <= MAX_X) && (position.y <= MAX_Y))
    {
        if (position.x + points <= MAX_X)
        {
            position.x += points;
            return_status = MOVE_OK;

            setNewPostion(&position);
        }
    }
    else
    {
        return_status = POSITION_WRONG;
    }

    return return_status;
}

MovementStatus moveUp(uint16_t points)
{
    Position position = getCurrentPosition();
    MovementStatus return_status = MOVE_NOT_POSSIBLE;

    if ((position.x <= MAX_X) && (position.y <= MAX_Y))
    {
        if (position.y >= points)
        {
            position.y -= points;
            return_status = MOVE_OK;

            setNewPostion(&position);
        }
    }
    else
    {
        return_status = POSITION_WRONG;
    }

    return return_status;
}

MovementStatus moveDown(uint16_t points)
{
    Position position = getCurrentPosition();
    MovementStatus return_status = MOVE_NOT_POSSIBLE;

    if ((position.x <= MAX_X) && (position.y <= MAX_Y))
    {
        if (position.y + points <= MAX_Y)
        {
            position.y += points;
            return_status = MOVE_OK;

            setNewPostion(&position);
        }
    }
    else
    {
        return_status = POSITION_WRONG;
    }

    return return_status;
}
