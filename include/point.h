#include "types.h"
#include "fixed.h"

#ifndef POINT_H
#define POINT_H

typedef struct POINT {
	FIXED x;
	FIXED y;
} ALIGN(4) POINT;

static inline POINT createPoint (FIXED x, FIXED y) {
	// Create a point from data
	POINT temp;
	temp.x = x;
	temp.y = y;
	return temp;
}

static inline POINT addPoint (POINT *a, POINT *b) {
	// Add two points
	POINT temp;
	temp.x = a->x + b->x;
	temp.y = a->y + b->y;
	return temp;
} 

#endif // POINT_H
