#include <gb/gb.h>
#include "defines.h"
#include "paddle.h"
#include "direction.h"

void move_paddle_sprites(struct Paddle *paddle)
{
    move_sprite(paddle->left, paddle->x, paddle->y);
    move_sprite(paddle->center, paddle->x + 8, paddle->y);
    move_sprite(paddle->right, paddle->x + 16, paddle->y);
    
    paddle->moved = 0;
}

void move_paddle(struct Paddle *paddle, enum DIRECTION dir)
{

    UINT8 new_x = paddle->x;

    if (dir == RIGHT)
        new_x += SPEED;
    else if (dir == LEFT)
        new_x -= SPEED;

    if (new_x <= 168 - 8 - 24 && new_x >= 8 + 8)
    {
        paddle->x = new_x;
        paddle->moved = 1;
    }
}