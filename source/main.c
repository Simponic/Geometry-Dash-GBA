#include <string.h>
#include "../include/input.h"
#include "../include/toolbox.h"
#include "../include/memmap.h"
#include "../include/types.h"
#include "../include/memdef.h"

#include "../include/point.h"
#include "../include/velocity.h"
#include "../include/playerObject.h"
#include "../sprites/player.h"

OBJ_ATTR obj_buffer[128];
OBJ_AFFINE *obj_aff_buffer= (OBJ_AFFINE*)obj_buffer; // Object affine-buffer

void obj_test() {
	int x, y;
	x = 10; y = 10;
    u32 tid= 0, pb= 0;
    OBJ_ATTR *player = &obj_buffer[0];

    obj_set_attr(player,
        ATTR0_SQUARE,
        ATTR1_SIZE_16,
        ATTR2_PALBANK(pb) | tid
    );

    obj_set_pos(player, x, y);

    while(1) {
        vid_vsync();
        key_poll();

        oam_copy(oam_mem, obj_buffer, 1);
    }
}

int main() {
    memcpy(&tile_mem[4][0], playerTiles, playerTilesLen);
    memcpy(pal_obj_mem, playerPal, playerPalLen);

    oam_init(obj_buffer, 128);

    REG_DISPCNT= DCNT_OBJ | DCNT_OBJ_1D;

	playerObject player = createPlayerObject(&obj_buffer[0], 0, 0);


    while(1) {
		vid_vsync();
		key_poll();

		if ((key_is_down(KEY_A) || key_hit(KEY_A)) && !player.isJumping) {
			player.vel.dy -= 9 << FIX_SHIFT;
		}

		updatePlayer(&player, 140);
		oam_copy(oam_mem, obj_buffer, 1);
	}

    return 0;
}
