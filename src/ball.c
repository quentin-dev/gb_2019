#include "ball.h"
#include "direction.h"

void move_ball(struct Ball *ball, enum DIRECTION dir)
{
    if (dir == UP || dir == DOWN)
    {
        UINT8 new_y = (dir == DOWN) ? ball->y + 1 : ball->y - 1;

        if (new_y >= 16 + 8 && new_y <= 160 - 8)
            ball->y = new_y;
    }
    else if (dir == LEFT || dir == RIGHT)
    {
        UINT8 new_x = (dir == LEFT) ? ball->x - 1 : ball->x + 1;

        if (new_x >= 8 + 8 && new_x <= 166 - 8 - 8)
            ball->x = new_x;
    }
}