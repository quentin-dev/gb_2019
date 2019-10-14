#ifndef BALL_H
#define BALL_H

/// @file ball.h
/// @author sunbro
/// @brief Struct definition and helper functions for the ball

#include <gb/gb.h>
#include "direction.h"

/// The ball the paddle interacts with
struct Ball
{
    /// Sprite id
    UINT8 sprite;
    /// X coordinate
    UINT8 x;
    /// Y cooordinate
    UINT8 y;
};

/// @brief Moves ball's position in the given direction dir
/// @param ball: The ball to move
/// @param dir: The direction to move in
/// @return Nothing
void move_ball(struct Ball *ball, enum DIRECTION dir);

#endif // ! BALL_H