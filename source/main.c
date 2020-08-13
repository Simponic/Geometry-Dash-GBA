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
#include "../include/camera.h"

#include "../sprites/player.h"
#include "../sprites/block.h"
#include "../sprites/spike.h"

OBJ_ATTR obj_buffer[128];
OBJ_AFFINE *obj_aff_buffer= (OBJ_AFFINE*)obj_buffer; // Object affine-buffer

int main() {
    memcpy(pal_obj_mem, blockPal, blockPalLen);
    memcpy(&tile_mem[4][0], playerTiles, playerTilesLen);
    memcpy(&tile_mem[4][4], blockTiles, blockTilesLen);
    memcpy(&tile_mem[4][8], spikeTiles, spikeTilesLen);

    oam_init(obj_buffer, 128);

    REG_DISPCNT= DCNT_OBJ | DCNT_OBJ_1D;

	playerObject player = createPlayerObject(&obj_buffer[0], &obj_aff_buffer[0],0, 0);
    player.camera = createCamera(-10, 0);
	int currentGroundLevel = 140;
	int currentXLevel = 1;

    while(1) {
		vid_vsync();
		player.camera.x += 1;
		key_poll();

		if (player.camera.x % 16 == 15) {
			currentXLevel++;
		}

		if ((key_is_down(KEY_A) || key_hit(KEY_A)) && !player.isJumping) {
			player.vel.dy -= 9 << FIX_SHIFT;
		}

		//updatePlayer(&player, 80);
		obj_affine_copy(obj_aff_mem, player.affine, 1);
		obj_copy(obj_mem, player.obj, 1);

        OBJ_ATTR blockObject, spikeObject;
        obj_set_attr(&blockObject,
            ATTR0_SQUARE,
            ATTR1_SIZE_16,
            ATTR2_PALBANK(0) | 4
        );
        obj_set_attr(&spikeObject,
            ATTR0_SQUARE,
            ATTR1_SIZE_16,
            ATTR2_PALBANK(0) | 8
        );
        int x, y;
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 15; j++){
                x = (j * 16);
                y = (i * 16);
                applyCameraShift(&player.camera, &x, &y);
                if (map1[i][j] == 1) {
					if (j == currentXLevel) {
						updatePlayer(&player, 16 * i - 16);
					}
                    obj_set_pos(&blockObject, x, y);
                    obj_copy(obj_mem + (16 * i + j) + 1, &blockObject, 1);
                }
                else if (map1[i][j] == 2) {
                    obj_set_pos(&spikeObject, x, y);
                    obj_copy(obj_mem + (16 * i + j) + 1, &spikeObject, 1);
                }
            }
        }

	}

    return 0;
}
