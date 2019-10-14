#ifndef DIRECTION_H
#define DIRECTION_H

/// @file direction.h
/// @author sunbro
/// @brief Enum definition and helper functions for direction

/// The different directions a game object can go
enum DIRECTION
{
    /// Y-
    UP,
    /// Y+
    DOWN,
    /// X-
    LEFT,
    /// X+
    RIGHT,
};

/// @brief Returns the opposite direction to dir
/// @param dir: The direction whose reverse we want
/// @return The opposite direction
enum DIRECTION reverse_direction(enum DIRECTION dir);

#endif // ! DIRECTION_H