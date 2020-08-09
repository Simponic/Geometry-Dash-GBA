#include "types.h"
#include "point.h"
#include "velocity.h"
#include "toolbox.h"
#include "fixed.h"

#ifndef PLAYEROBJECT_H
#define PLAYEROBJECT_H

#define GRAVITY 0.75

typedef struct playerObject {
	VELOCITY vel;
	POINT pt;
	u32 rotation; // Rotation amount
	OBJ_ATTR *obj; // Attributes of the object for GBA
	int pallete_bank; // Index of pallete
	int tile_id; // Index of player tile
	int isJumping;
} ALIGN(4) playerObject; // Word-align to ensure corruption doesn't occur

static inline void initializePlayerObject (playerObject *object) {
	// Initialize the point and velocity of an object
	object->vel = createVelocity(0, 0);
	object->pt = createPoint(20 << FIX_SHIFT, 100 << FIX_SHIFT);
}

static inline playerObject createPlayerObject (OBJ_ATTR *obj_buffer, int pallete_bank, int tile_id) {
	// Create a player object from data
	playerObject temp;
	initializePlayerObject(&temp);
	temp.rotation = 0;
	temp.obj = obj_buffer;
	temp.pallete_bank = pallete_bank;
	temp.tile_id = tile_id;
	temp.isJumping = 0;
	obj_set_attr(temp.obj,
			ATTR0_SQUARE, // Set attribute 1 to be a square
			ATTR1_SIZE_16, // Set size to 16 x 16
			ATTR2_PALBANK(pallete_bank) | tile_id // Which pallete to use, as we are in 
			// 16-color mode
	);
	obj_set_pos(temp.obj, temp.pt.x >> FIX_SHIFT, temp.pt.y >> FIX_SHIFT);
	return temp;
}

static inline void applyGravity (playerObject *object) {
	// Apply a gravity constant to a player
	object->vel.dy += float_to_fixed(GRAVITY);
	// This is a weird convention to have gravity in the positive direction,
	// but I don't want to deal with coordinate changing. Too lazy
}

static inline void updatePlayer (playerObject *object, u32 GROUND_LEVEL) {
	// Update the position of a player object
	updatePoint(&object->pt, &object->vel);
	if (object->pt.y >> FIX_SHIFT >= GROUND_LEVEL) {
		// Only apply gravity if player is not touching the ground
		object->isJumping = 0;
		object->pt.y = GROUND_LEVEL << FIX_SHIFT; // Don't go through ground
		object->vel.dy = 0;
	}
	else {
		object->isJumping = 1;
		applyGravity(object);
	}
	// Update the player object's attributes' position
	obj_set_pos(object->obj, object->pt.x >> FIX_SHIFT, object->pt.y >> FIX_SHIFT);
	// Update the player's second attribute (tile and pallete bank)
	object->obj->attr2 = ATTR2_BUILD(object->tile_id, object->pallete_bank, 0);
}

#endif // PLAYEROBJECT_H
