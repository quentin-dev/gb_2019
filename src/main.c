#include <stdio.h>
#include <gb/gb.h>

#include "mapmap.h"
#include "mapset.h"
#include "player_sprites.h"

#include "player.h"

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

UINT8 collides_with_tree(UINT8 *tiles)
{
    UINT8 tree[6] = { 0x0, 0x1, 0x7, 0x8, 0x13, 0x14 };

    for (UINT8 i = 0; i < 2; ++i)
    {
        for (UINT8 j = 0; j < 6; ++j)
        {
            if (tiles[i] == tree[j])
                return 1;
        }
    }

    return 0;
}

UINT8 collides_with_house(UINT8 *tiles)
{
    UINT8 house[28] = {
        0x0B, 0x0C, 0x0D,
        0x15, 0x16, 0x17,
        0x1B, 0x1C, 0x1D,
        0x23, 0x24, 0x25,
        0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31,
        0x32, 0x33, 0x34, 0x35,
        0x36, 0x37, 0x38, 0x39, 0x3A,
    };

    for (UINT8 i = 0; i < 2; ++i)
    {
        for (UINT8 j = 0; j < 28; ++j)
        {
            if (tiles[i] == house[j])
                return 1;
        }
    }

    return 0;
}

void main(void)
{
    UINT8 keys = 0;
    UINT8 frame_skip = 8;

    Player *player = create_player();

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

    move_sprite(PLAYER_SPRITE_L_ID, player->x, player->y);
    set_sprite_prop(PLAYER_SPRITE_L_ID, S_PALETTE);

    move_sprite(PLAYER_SPRITE_R_ID, player->x + 8, player->y);
    set_sprite_prop(PLAYER_SPRITE_R_ID, S_PALETTE);

    UINT8 tile[2] = { 255, 255, };

    while (1)
    {
        keys = joypad();

        UINT8 prev_x = player->x;
        UINT8 prev_y = player->y;

        if (keys & J_UP)
            update_direction_data(player, PLAYER_DIRECTION_UP);
        else if (keys & J_DOWN)
            update_direction_data(player, PLAYER_DIRECTION_DOWN);
        else if (keys & J_LEFT)
            update_direction_data(player, PLAYER_DIRECTION_LEFT);
        else if (keys & J_RIGHT)
            update_direction_data(player, PLAYER_DIRECTION_RIGHT);
        else
        {
            player->is_walking = 0;
            frame_skip = 1;
        }

        if (player->is_walking)
        {
            get_bkg_tiles(player->x / 8, player->y / 8, 2, 1, tile);

            if (collides_with_tree(tile) == 1 || collides_with_house(tile) == 1)
            {
                player->x = prev_x;
                player->y = prev_y;
            }
            else
                scroll_bkg(player->x - prev_x, player->y - prev_y);

            frame_skip -= 1;
            if (!frame_skip)
                frame_skip = 8;
            else
            {
                wait_vbl_done();
                continue;
            }
        }
        else
        {
            player->animation_frame = 0;
        }

        update_sprite_animation(PLAYER_SPRITE_L_ID, PLAYER_SPRITE_ANIM_L,
                player->direction, player->animation_frame);

        player->animation_frame = update_sprite_animation(PLAYER_SPRITE_R_ID,
                PLAYER_SPRITE_ANIM_R, player->direction, player->animation_frame);

        wait_vbl_done();
    }
}
