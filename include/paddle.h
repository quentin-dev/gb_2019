#ifndef PADDLE_H
#define PADDLE_H

#include <gb/gb.h>
#include "direction.h"

struct Paddle
{
    UINT8 left;
    UINT8 center;
    UINT8 right;
    UINT8 x;
    UINT8 y;
    UINT8 moved;
};

void move_paddle_sprites(struct Paddle *paddle);
void move_paddle(struct Paddle *paddle, enum DIRECTION dir);

#endif // ! PADDLE_H