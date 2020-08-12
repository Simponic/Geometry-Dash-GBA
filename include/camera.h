#include "types.h"

#ifndef CAMERA_H
#define CAMERA_H

typedef struct CAMERA {
    int x;
    int y;
} ALIGN(4) CAMERA;

CAMERA createCamera();
void applyCameraShift();

#endif // CAMERA_H
