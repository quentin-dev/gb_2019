#include "direction.h"

enum DIRECTION reverse_direction(enum DIRECTION dir)
{
    if (dir == RIGHT)
        return LEFT;
    if (dir == LEFT)
        return RIGHT;

    if (dir == UP)
        return DOWN;
    if (dir == DOWN)
        return UP;

    return dir;
}