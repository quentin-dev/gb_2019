# gb_2019

## Setup

1) Make sure you have SDCC installed on your machine
2) `git submodule update --init`

## Compiling

### Library

You must build the gbdk-n library to be able to compile the game.
You can do so by calling `make library` or `make all`.

### Game

To compile the game, run `make` or `make game`.
The result is the `build/game.gb` file.

### Cleaning

You can clean the build directory by running `make clean`.

## State of the project

### Currently

The game is "playable", meaning you can break the bricks and move the paddle.

### Probably

The collisions are not exactly perfect yet, there is still a slight offset due
to the way position in handled. Also, the code should be refactored a bit to
make it more readable.

### Eventually

The following things should be added to make this a full game:

*   A game over screen
*   A start menu
*   Sound effects / music