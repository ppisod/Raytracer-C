//
// Created by JackL on 8/23/26.
//

#ifndef RAYTRACER_MATERIALS_H
#define RAYTRACER_MATERIALS_H

#include "../lib/vec3.h"

typedef enum {
    Mat_Lambertian,
    Mat_Metal,
} MaterialType;

typedef struct {
    MaterialType type;
    Vec3 albedo; // Per channel reflectance
    double fuzz; // for Mat_Metal 1->0 mirrorness
} Material;

#endif //RAYTRACER_MATERIALS_H