#include <stdlib.h>

#include "player.h"

Player *create_player()
{
    Player *player = malloc(sizeof(Player));
    if (player == NULL)
        return NULL;
     
    player->x = 80;
    player->y = 72;
    player->direction = PLAYER_DIRECTION_DOWN;
    player->animation_frame = 0;
    player->is_walking = 0;

    return player;
}

void update_direction_data(Player *player, UINT8 direction)
{
    switch(direction)
    {
    case PLAYER_DIRECTION_DOWN:
        player->y += 1;
        break;
    case PLAYER_DIRECTION_UP:
        player->y -= 1;
        break;
    case PLAYER_DIRECTION_LEFT:
        player->x -= 1;
        break;
    case PLAYER_DIRECTION_RIGHT:
        player->x += 1;
        break;
    default:
        return;
    }

    player->direction = direction;
    player->is_walking = 1;
}

void free_player(Player *player)
{
    free(player);
}
