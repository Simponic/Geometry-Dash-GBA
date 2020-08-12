#include "../include/camera.h"

CAMERA createCamera (int x, int y) {
    // Create camera from a point
    CAMERA temp;
    temp.x = x;
    temp.y = y;
    return temp;
}

void applyCameraShift (CAMERA *camera, int *x, int *y) {
    // Apply camera shift to a coordinate
    *x = *x - camera->x;
    *y = *y - camera->y;
}
