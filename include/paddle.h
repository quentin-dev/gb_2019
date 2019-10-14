#ifndef PADDLE_H
#define PADDLE_H

/// @file paddle.h
/// @author sunbro
/// @brief Struct definition and helper functions for the paddle

#include <gb/gb.h>
#include "direction.h" 

/// The player controlled paddle
struct Paddle
{
    /// Left sprite id
    UINT8 left;
    /// Center sprite id
    UINT8 center;
    /// Right sprite id
    UINT8 right;
    /// X coordinate
    UINT8 x;
    /// Y coordinate
    UINT8 y;
    /// Has the paddle moved already
    UINT8 moved;
};

/// @brief Moves paddle's sprites to paddle's position
/// @param paddle: The paddle whose sprites to move
/// @return Nothing
void move_paddle_sprites(struct Paddle *paddle);

/// @brief Moves the paddle in the given direction
/// @brief Only updates the position, does not move the paddle's sprites
/// @param paddle: The paddle to move
/// @param dir: The direction in which to move
/// @return Nothing
void move_paddle(struct Paddle *paddle, enum DIRECTION dir);

#endif // ! PADDLE_H