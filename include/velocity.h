#include "types.h"
#include "fixed.h"
#include "point.h"

#ifndef VELOCITY_H
#define VELOCITY_H

typedef struct VELOCITY {
	FIXED dx;
	FIXED dy;
} ALIGN(4) VELOCITY;

static inline VELOCITY createVelocity (FIXED dx, FIXED dy) {
	// Create velocity from data
	VELOCITY temp;
	temp.dx = dx;
	temp.dy = dy;
	return temp;
}

static inline VELOCITY addVelocities (VELOCITY *a, VELOCITY *b) {
	// Add two velocities
	VELOCITY temp;
	temp.dx = a->dx + b->dx;
	temp.dy = a->dy + b->dy;
	return temp;
}

static inline void updatePoint (POINT *pt, VELOCITY *vel) {
	// Update a point with a velocity
	pt->x += vel->dx;
	pt->y += vel->dy;
}

#endif // VELOCITY_H
