#include <gb/gb.h>
// Sprites
#include "tilesets/breakoutset.h"
#include "tilemaps/breakoutmap.h"
// Defines
#include "defines.h"
// Engine constructs
#include "direction.h"
#include "collision.h"
// Game objects
#include "paddle.h"
#include "ball.h"

void title_screen(void)
{
    waitpad(J_START);
    waitpadup();
}

void main(void)
{
    title_screen();

    set_bkg_data(128, TILESET_TILE_COUNT, TILESET);
    set_bkg_tiles(0, 0, TILEMAP_WIDTH, TILEMAP_HEIGHT, TILEMAP);
    SHOW_BKG;

    set_sprite_tile(0, 143); // Ball : 128 + 0x0F

    struct Ball ball = { 0, 50, 120 };

    UINT8 idx = 140; // 128 + 0x0C

    set_sprite_tile(1, idx); // Paddle left
    set_sprite_tile(2, idx + 1); // Paddle middle
    set_sprite_tile(3, idx + 2); // Paddle right

    struct Paddle paddle = { 1, 2, 3, 76, 152, 0};

    move_sprite(ball.sprite, ball.x, ball.y); // Set ball position

    // Set Paddle position
    move_paddle_sprites(&paddle);

    SHOW_SPRITES;

    // UINT8 keys = 0;

    enum DIRECTION dir = DOWN;
    enum DIRECTION side = UP;

    unsigned char tiles[2];

    unsigned char blank[2] = { 0x80, 0x80 };

    while(1)
    {

        UINT8 keys = joypad();

        if (keys & J_RIGHT)
            move_paddle(&paddle, RIGHT);
        else if (keys & J_LEFT)
            move_paddle(&paddle, LEFT);

        if (check_collision(&ball, &paddle))
        {
            dir = UP;

            if (ball.x < paddle.x + 12)
                side = LEFT;
            else if (ball.x > paddle.x + 12)
                side = RIGHT;
            else
                side = UP;
        }
        else
        {
            if (side != UP && check_brick(&ball, side))
            {
                side = reverse_direction(side);
            }

            if (check_brick(&ball, dir))
            {
                dir = reverse_direction(dir);
            }

            if (ball.y <= 16 + 8)
                dir = DOWN;
            if (ball.x <= 8 + 8)
                side = RIGHT;
            else if (ball.x >= 166 - 8 - 8)
                side = LEFT;
        }

        if (side != UP)
            move_ball(&ball, side);

        move_ball(&ball, dir);

        if (paddle.moved)
            move_paddle_sprites(&paddle);

        move_sprite(ball.sprite, ball.x, ball.y);

        wait_vbl_done();
    }
}
