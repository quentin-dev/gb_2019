#include <stdio.h>
#include <gb/gb.h>
#include <gb/console.h>
#include "tilemap.h"
#include "tileset.h"

int main(void)
{
    set_bkg_data(0, TILESET_TILE_COUNT, TILESET);
    set_bkg_tiles(0, 0, TILEMAP_WIDTH, TILEMAP_HEIGHT, TILEMAP);
    SHOW_BKG;

    UINT8 keys = 0;

    while (1)
    {
        keys = joypad();

        if (keys & J_LEFT)
            scroll_bkg(-1, 0);
        if (keys & J_RIGHT)
            scroll_bkg(1, 0);
        if (keys & J_UP)
            scroll_bkg(0, -1);
        if (keys & J_DOWN)
            scroll_bkg(0, 1);

        if (keys & J_START)
            move_bkg(0, 0);

        wait_vbl_done();
    }

    return 0;
}
