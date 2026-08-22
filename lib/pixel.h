//
// Created by JackL on 8/22/26.
//

#ifndef RAYTRACER_PIXEL_H
#define RAYTRACER_PIXEL_H

#include "vec3.h"

typedef struct {
    unsigned char r, g, b;
} Pixel;

Pixel VecToPixel (Vec3 color);

#endif //RAYTRACER_PIXEL_H