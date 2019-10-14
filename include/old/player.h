#ifndef PLAYER_H
#define PLAYER_H

#include <types.h>

#define PLAYER_SPRITE_L_ID 0
#define PLAYER_SPRITE_R_ID 1
#define PLAYER_DIRECTION_DOWN 0
#define PLAYER_DIRECTION_UP 6
#define PLAYER_DIRECTION_RIGHT 12
#define PLAYER_DIRECTION_LEFT 18

struct Player
{
    UINT8 x;
    UINT8 y;

    UINT8 direction;
    UINT8 animation_frame;
    UINT8 is_walking;
};

typedef struct Player Player;

Player *create_player();
void update_direction_data(Player *player, UINT8 direction);
void free_player(Player *player);

#endif
