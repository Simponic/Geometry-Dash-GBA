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

int main() {
    memcpy(&tile_mem[4][0], playerTiles, playerTilesLen);
    memcpy(pal_obj_mem, playerPal, playerPalLen);

    oam_init(obj_buffer, 128);

    REG_DISPCNT= DCNT_OBJ | DCNT_OBJ_1D;

	playerObject player = createPlayerObject(&obj_buffer[0], &obj_aff_buffer[0],0, 0);

    while(1) {
		vid_vsync();
		key_poll();

		if ((key_is_down(KEY_A) || key_hit(KEY_A)) && !player.isJumping) {
			player.vel.dy -= 9 << FIX_SHIFT;
		}

		updatePlayer(&player, 120);
		obj_affine_copy(obj_aff_mem, player.affine, 1);
		obj_copy(obj_mem, player.obj, 1);
	}

    return 0;
}
