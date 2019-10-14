#include <gb/gb.h>
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