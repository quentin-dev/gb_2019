#include <gb/gb.h>

#include "breakoutset.h"
#include "breakoutmap.h"

#define SPRITE_OFFSET 128
#define SPEED 2

enum DIRECTION
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
};

struct Ball
{
    UINT8 sprite;
    UINT8 x;
    UINT8 y;
};

struct Paddle
{
    UINT8 left;
    UINT8 center;
    UINT8 right;
    UINT8 x;
    UINT8 y;
    UINT8 moved;
};

void move_paddle_sprites(struct Paddle *paddle)
{
    move_sprite(paddle->left, paddle->x, paddle->y);
    move_sprite(paddle->center, paddle->x + 8, paddle->y);
    move_sprite(paddle->right, paddle->x + 16, paddle->y);
    
    paddle->moved = 0;
}

void move_paddle(struct Paddle *paddle, enum DIRECTION dir)
{

    UINT8 new_x = paddle->x;

    if (dir == RIGHT)
        new_x += SPEED;
    else if (dir == LEFT)
        new_x -= SPEED;

    if (new_x <= 168 - 8 - 24 && new_x >= 8 + 8)
    {
        paddle->x = new_x;
        paddle->moved = 1;
    }
}

void move_ball(struct Ball *ball, enum DIRECTION dir)
{
    if (dir == UP || dir == DOWN)
    {
        UINT8 new_y = (dir == DOWN) ? ball->y + 1 : ball->y - 1;

        if (new_y >= 16 + 8 && new_y <= 160 - 8)
            ball->y = new_y;
    }
    else if (dir == LEFT || dir == RIGHT)
    {
        UINT8 new_x = (dir == LEFT) ? ball->x - 1 : ball->x + 1;

        if (new_x >= 8 + 8 && new_x <= 166 - 8 - 8)
            ball->x = new_x;
    }
}

// FIXME: Implement collision detection
// void check_collision(struct Ball *ball, struct Paddle *paddle)

void main(void)
{
    set_bkg_data(128, TILESET_TILE_COUNT, TILESET);
    set_bkg_tiles(0, 0, TILEMAP_WIDTH, TILEMAP_HEIGHT, TILEMAP);
    SHOW_BKG;

    set_sprite_tile(0, 128 + 0x0F); // Ball

    struct Ball ball = { 0, 50, 120 };

    set_sprite_tile(1, 128 + 0x0C); // Paddle left
    set_sprite_tile(2, 128 + 0x0D); // Paddle middle
    set_sprite_tile(3, 128 + 0x0E); // Paddle right

    struct Paddle paddle = { 1, 2, 3, 76, 152, 0};

    move_sprite(ball.sprite, ball.x, ball.y); // Set ball position

    // Set Paddle position
    move_paddle_sprites(&paddle);

    SHOW_SPRITES;

    UINT8 keys = 0; 

    while(1)
    {

        keys = joypad();

        if (keys & J_RIGHT)
            move_paddle(&paddle, RIGHT);
        else if (keys & J_LEFT)
            move_paddle(&paddle, LEFT);

        move_ball(&ball, DOWN);
    
        // check_collision(&ball, &paddle);

        if (paddle.moved)
            move_paddle_sprites(&paddle);

        move_sprite(ball.sprite, ball.x, ball.y);

        wait_vbl_done();
    }
}
