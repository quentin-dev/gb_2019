#include <gb/gb.h>

#include "mapmap.h"
#include "mapset.h"
#include "player_sprites.h"

#define PLAYER_SPRITE_L_ID 0
#define PLAYER_SPRITE_R_ID 1


#define PLAYER_DIRECTION_DOWN 0
#define PLAYER_DIRECTION_UP 6
#define PLAYER_DIRECTION_RIGHT 12
#define PLAYER_DIRECTION_LEFT 18

void flip_sprite_horiz(UINT8 sprite_id)
{
    set_sprite_prop(sprite_id, get_sprite_prop(sprite_id) | S_FLIPX);
}

void unflip_sprite_horiz(UINT8 sprite_id)
{
    set_sprite_prop(sprite_id, get_sprite_prop(sprite_id) & ~S_FLIPX);
}

UINT8 update_sprite_animation(UINT8 sprite_id, UINT8 *anim, UINT8 direction, UINT8 frame)
{
    UINT8 len = anim[direction];
    UINT8 flip = anim[direction + 1];
    UINT8 tile_id = anim[direction + 2 + frame];

    if (flip)
        flip_sprite_horiz(sprite_id);
    else
        unflip_sprite_horiz(sprite_id);

    set_sprite_tile(sprite_id, tile_id);

    return (frame + 1) % len;
}

void main(void)
{

    UINT8 keys = 0;
    UINT8 frame_skip = 8;

    UINT8 player_x = 80;
    UINT8 player_y = 72;
    UINT8 player_direction = PLAYER_DIRECTION_DOWN;
    UINT8 player_animation_frame = 0;
    UINT8 is_player_walking = 0;

    UINT8 PLAYER_SPRITE_ANIM_L[] = {
        4, 0, 0, 4, 0, 8,
        4, 0, 12, 16, 12, 20,
        4, 0, 24, 28, 24, 32,
        4, 1, 26, 30, 26, 34,
    };

    UINT8 PLAYER_SPRITE_ANIM_R[] = {
        4, 0, 2, 6, 2, 10,
        4, 0, 14, 18, 14, 22,
        4, 0, 26, 30, 26, 34,
        4, 1, 24, 28, 24, 32,
    };

    set_bkg_data(0, TILESET_TILE_COUNT, TILESET);
    set_bkg_tiles(0, 0, TILEMAP_WIDTH, TILEMAP_HEIGHT, TILEMAP);
    SHOW_BKG;

    set_sprite_data(0, PLAYER_SPRITES_TILE_COUNT, PLAYER_SPRITES);
    SPRITES_8x16;
    SHOW_SPRITES;

    move_sprite(PLAYER_SPRITE_L_ID, player_x, player_y);
    set_sprite_prop(PLAYER_SPRITE_L_ID, S_PALETTE);

    move_sprite(PLAYER_SPRITE_R_ID, player_x + 8, player_y);
    set_sprite_prop(PLAYER_SPRITE_R_ID, S_PALETTE);

    while (1)
    {
        wait_vbl_done();

        keys = joypad();

        if (keys & J_UP)
        {
            player_direction = PLAYER_DIRECTION_UP;
            is_player_walking = 1;
            player_y -= 1;
        }
        else if (keys & J_DOWN)
        {
            player_direction = PLAYER_DIRECTION_DOWN;
            is_player_walking = 1;
            player_y += 1;
        }
        else if (keys & J_LEFT)
        {
            player_direction = PLAYER_DIRECTION_LEFT;
            is_player_walking = 1;
            player_x -= 1;
        }
        else if (keys & J_RIGHT)
        {
            player_direction = PLAYER_DIRECTION_RIGHT;
            is_player_walking = 1;
            player_x += 1;
        }
        else
        {
            is_player_walking = 0;
            frame_skip = 1;
        }

        if (is_player_walking)
        {
            move_sprite(PLAYER_SPRITE_L_ID, player_x, player_y);
            move_sprite(PLAYER_SPRITE_R_ID, player_x + 8, player_y);

            frame_skip -= 1;
            if (!frame_skip)
                frame_skip = 8;
        }
        else
        {
            player_animation_frame = 0;
        }

        update_sprite_animation(PLAYER_SPRITE_L_ID, PLAYER_SPRITE_ANIM_L,
                player_direction, player_animation_frame);

        player_animation_frame = update_sprite_animation(PLAYER_SPRITE_R_ID,
                PLAYER_SPRITE_ANIM_R, player_direction, player_animation_frame);
    }
}
