#include <gb/gb.h>
#include "defines.h"
#include "direction.h"
#include "ball.h"
#include "paddle.h"
#include "collision.h"

UINT8 check_collision(struct Ball *ball, struct Paddle *paddle)
{
    UINT8 b_rx = ball->x + 8;
    UINT8 b_ry = ball->y + 8;

    UINT8 p_rx = paddle->x + 24;
    UINT8 p_ry = paddle->y + 8;


    UINT8 x_overlap = (ball->x >= paddle->x && ball->x <=p_rx) ||
                      (paddle->x >= ball->x && paddle->x <= b_rx);

    UINT8 y_overlap = (ball->y >= paddle->y && ball->y <= p_ry) ||
                      (paddle->y >= ball->y && paddle->y <= b_ry);

    return x_overlap && y_overlap;
}

UINT8 check_brick(struct Ball *ball, enum DIRECTION dir)
{

    UINT8 next_ball_x = ball->x;

    if (dir == RIGHT)
        next_ball_x += 1;
    else if (dir == LEFT)
        next_ball_x -= 1;

    UINT8 next_ball_y = ball->y;

    if (dir == DOWN)
        next_ball_y += 1;
    else if (dir == UP)
        next_ball_y -= 1;

    UINT8 next_cell_x = (next_ball_x - 8) / 8;
    UINT8 next_cell_y = (next_ball_y - 16) / 8;

    UINT8 next_cell[1] = { 0 };

    get_bkg_tiles(next_cell_x, next_cell_y, 1, 1, next_cell);

    if (next_cell[0] == BRICK_L)
    {
        remove_brick(next_cell_x, next_cell_y);
        ball->bricks += 1;
    }
    else if (next_cell[0] == BRICK_R)
    {
        remove_brick(next_cell_x - 1, next_cell_y);
        ball->bricks += 1;
    }

    return next_cell[0] != EMPTY_TILE;
}

void remove_brick(UINT8 x, UINT8 y)
{
    UINT8 cells[2] = { EMPTY_TILE, EMPTY_TILE };
    set_bkg_tiles(x, y, 2, 1, cells);
}