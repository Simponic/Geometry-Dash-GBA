#include "types.h"

#ifndef SINLUT_H
#define SINLUT_H

extern const short sin_lut[512];

static inline s32 lu_sin(u32 theta)
{   return sin_lut[(theta>>7)&0x1FF];   }

//! Look-up a cosine value
static inline s32 lu_cos(u32 theta)
{   return sin_lut[((theta>>7)+128)&0x1FF]; }

#endif //SINLUT_H
