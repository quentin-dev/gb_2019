#ifndef DIRECTION_H
#define DIRECTION_H

enum DIRECTION
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
};

enum DIRECTION reverse_direction(enum DIRECTION dir);

#endif // ! DIRECTION_H