//
// Created by JackL on 8/22/26.
//

#include "pixel.h"

#include "vec3.h"

Pixel VecToPixel (const Vec3 color) {
    return (Pixel)
        {
            (unsigned char) (color.x * 255.999),
            (unsigned char) (color.y * 255.999),
            (unsigned char) (color.z * 255.999)
        };
}
