#ifndef BALL_H
#define BALL_H

#include <gb/gb.h>
#include "direction.h"

struct Ball
{
    UINT8 sprite;
    UINT8 x;
    UINT8 y;
};

void move_ball(struct Ball *ball, enum DIRECTION dir);

#endif // ! BALL_H