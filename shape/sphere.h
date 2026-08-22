//
// Created by JackL on 8/22/26.
//

#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H

#include "../lib/vec3.h"

typedef struct {
    Vec3 origin;
    double radius;
} Sphere;

double RayHitsSphere (Sphere s, Ray r);

#endif //RAYTRACER_SPHERE_H