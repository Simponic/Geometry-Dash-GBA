#include "types.h"
#include "point.h"
#include "velocity.h"
#include "toolbox.h"
#include "fixed.h"
#include "sinlut.h"
#include "camera.h"

#ifndef PLAYEROBJECT_H
#define PLAYEROBJECT_H

#define GRAVITY 0.75

typedef struct playerObject {
	CAMERA camera;
	VELOCITY vel;
	POINT pt;
	u32 rotation; // Rotation amount
	OBJ_ATTR *obj; // Attributes of the object for GBA
	OBJ_AFFINE *affine; // Affine transformations
	int pallete_bank; // Index of pallete
	int tile_id; // Index of player tile
	int isJumping;
} ALIGN(4) playerObject; // Word-align to ensure corruption doesn't occur

void initializePlayerObject();
playerObject createPlayerObject();
void applyGravity();
void scalePlayer();
void updatePlayer();


#endif // PLAYEROBJECT_H
