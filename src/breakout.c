#include <gb/gb.h>

#include "tilesets/breakoutset.h"
#include "tilemaps/breakoutmap.h"

#include "defines.h"

#include "direction.h"
#include "paddle.h"
#include "ball.h"

UINT8 check_collision(struct Ball *ball, struct Paddle *paddle)
{
    UINT8 b_rx = ball->x + 8;
    UINT8 b_ry = ball->y + 8;

    UINT8 p_rx = paddle->x + 24;
    UINT8 p_ry = paddle->y + 8;


    UINT8 x_overlap = (ball->x >= paddle->x && ball->x <=p_rx) ||
                      (paddle->x >= ball->x && paddle->x <= b_rx);

    UINT8 y_overlap = (ball->y >= paddle->y && ball->y <= p_ry) ||
                      (paddle->y >= ball->y && paddle->y <= b_ry);

    return x_overlap && y_overlap;
}

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

void main(void)
{
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

    UINT8 keys = 0;

    enum DIRECTION dir = DOWN;
    enum DIRECTION side = UP;

    unsigned char tiles[2];

    unsigned char blank[2] = { 0x80, 0x80 };

    while(1)
    {

        keys = joypad();

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
            get_bkg_tiles((ball.x / 8) + 1, (ball.y / 8) + 2, 2, 1, tiles);

            if (tiles[0] == 0x88 || tiles[1] == 0x89 || tiles[1] == 0x88)
            {
                set_bkg_tiles((ball.x / 8) + 1, (ball.y / 8) + 2, 2, 1, blank);
                dir = reverse_direction(dir);
            }
            else if (tiles[0] == 0x89)
            {
                set_bkg_tiles(((ball.x) / 8), ((ball.y) / 8) + 2, 2, 1, blank);
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
