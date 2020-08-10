#include "../include/playerObject.h"

void initializePlayerObject (playerObject *object) {
	// Initialize the point and velocity of a player object
	object->vel = createVelocity(0, 0);
	object->pt = createPoint(20 << FIX_SHIFT, 100 << FIX_SHIFT);
}

playerObject createPlayerObject (OBJ_ATTR *obj_buffer, OBJ_AFFINE *affine_buffer, int pallete_bank, int tile_id) {
	// Create a player object from data
	obj_affine_identity(affine_buffer);
	playerObject temp;
	initializePlayerObject(&temp);
	temp.rotation = 0;
	temp.obj = obj_buffer;
	temp.affine = affine_buffer;	
	temp.pallete_bank = pallete_bank;
	temp.tile_id = tile_id;
	temp.isJumping = 0;
	obj_set_attr(temp.obj,
			ATTR0_SQUARE | ATTR0_AFF | ATTR0_AFF_DBL_BIT, // Set attribute 1 to be a square using affine
			ATTR1_SIZE_16 | ATTR1_AFF_ID(0), // Set size to 16 x 16
			ATTR2_PALBANK(pallete_bank) | tile_id // Which pallete to use, as we are in 
			// 16-color mode
	);
	obj_set_pos(temp.obj, temp.pt.x >> FIX_SHIFT, temp.pt.y >> FIX_SHIFT);
	return temp;
}

void applyGravity (playerObject *object) {
	// Apply a gravity constant to a player
	object->vel.dy += float_to_fixed(GRAVITY);
	// This is a weird convention to have gravity in the positive direction,
	// but I don't want to deal with coordinate changing. Too lazy
}

void scalePlayer (playerObject *object, u32 scaleX, u32 scaleY) {
	// Scale the player's sprite
	// Maximum 0.5
	object->affine->pa = scaleX;  object->affine->pb = 0     ;
	object->affine->pc = 0     ;  object->affine->pd = scaleY;
}

void rotatePlayer (playerObject *object) {
	// Rotate the player's sprite
	int sinAlpha = lu_sin(object->rotation >> 4) >> 4;
	int cosAlpha = lu_cos(object->rotation >> 4) >> 4;

	object->affine->pa = cosAlpha; object->affine->pb =-sinAlpha;
	object->affine->pc = sinAlpha; object->affine->pd = cosAlpha;
}

u32 roundToNearest90Degrees(u32 rotation) {
	// Round a rotation to the nearest 90 degree equivalent of "binary radians"
	// (Where 2pi = 0xFFFF and 0pi = 0)
	u32 twoPi = 0xFFFF << 4;
	u32 pi = 0x8000 << 4;
	u32 halfPi = 0x4000 << 4;
	u32 quarterPi = 0x2000 << 4;

	
	if (rotation > quarterPi && rotation < 3 * quarterPi) {
		return halfPi;
	}
	else if (rotation > 3 * quarterPi && rotation < (pi + quarterPi)) {
		return pi;
	}
	else if (rotation > (pi + quarterPi) && rotation < (pi + 3*quarterPi)) {
		return pi + halfPi;
	}
	else if (rotation < quarterPi || rotation > (twoPi - quarterPi)) {
		return 1;
	}
	return 1;
}

void updatePlayer (playerObject *object, u32 GROUND_LEVEL) {
	// Update the position of a player object
	updatePoint(&object->pt, &object->vel);
	if (object->pt.y >> FIX_SHIFT >= GROUND_LEVEL) {
		// Only apply gravity if player is not touching the ground
		object->isJumping = 0;
		object->pt.y = GROUND_LEVEL << FIX_SHIFT; // Don't go through ground
		object->vel.dy = 0;
		object->rotation = roundToNearest90Degrees(object->rotation);
	}
	else {
		object->isJumping = 1;
		applyGravity(object);
		object->rotation += 100 << 8;
	}
	rotatePlayer(object);
	// Update the player object's attributes' position
	obj_set_pos(object->obj, object->pt.x >> FIX_SHIFT, object->pt.y >> FIX_SHIFT);
	// Update the player's second attribute (tile and pallete bank)
	object->obj->attr2 = ATTR2_BUILD(object->tile_id, object->pallete_bank, 0);
}

