#ifndef COLLISION_H
#define COLLISION_H

/// @file collision.h
/// @author sunbro
/// @brief Helper functions for checking collisions

#include <gb/gb.h>
#include "ball.h"
#include "direction.h"
#include "paddle.h"

/// @brief Checks if there is a collision between ball and paddle
/// @param ball: The ball
/// @param paddle: The paddle
/// @return 0 if there is no collision, 1 if there is
UINT8 check_collision(struct Ball *ball, struct Paddle *paddle);

UINT8 check_brick(struct Ball *ball, enum DIRECTION dir);

void remove_brick(UINT8 x, UINT8 y);

#endif // ! COLLISION_H