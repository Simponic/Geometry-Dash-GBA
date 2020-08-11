#include <string.h>
#include "../include/input.h"
#include "../include/toolbox.h"
#include "../include/memmap.h"
#include "../include/types.h"
#include "../include/memdef.h"
#include "../include/point.h"
#include "../include/velocity.h"
#include "../include/playerObject.h"
#include "../include/map.h"

#include "../sprites/player.h"
#include "../sprites/block.h"

OBJ_ATTR obj_buffer[128];
OBJ_AFFINE *obj_aff_buffer= (OBJ_AFFINE*)obj_buffer; // Object affine-buffer

int main() {
    memcpy(&tile_mem[4][0], playerTiles, playerTilesLen);
    memcpy(pal_obj_mem, playerPal, playerPalLen);
    memcpy(&tile_mem[4][4], blockTiles, blockTilesLen);

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

        OBJ_ATTR tileObject;
        for (int i = 0; i < 7; i++) {
            for (int j = 0; j < 12; j++){
                obj_set_attr(&tileObject,
                    ATTR0_SQUARE,
                    ATTR1_SIZE_16,
                    ATTR2_PALBANK(0) | 4
                );
                obj_set_pos(&tileObject, (j * 16), (i * 16));
                if (map1[i][j]) {
                    obj_copy(obj_mem + (17 * i + j) + 1, &tileObject, 1);
                }
            }
        }

	}

    return 0;
}
