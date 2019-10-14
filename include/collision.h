#ifndef COLLISION_H
#define COLLISION_H

#include <gb/gb.h>
#include "ball.h"
#include "paddle.h"

UINT8 check_collision(struct Ball *ball, struct Paddle *paddle);

#endif // ! COLLISION_H