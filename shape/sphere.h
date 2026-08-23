//
// Created by JackL on 8/22/26.
//

#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H

#include "../lib/vec3.h"
#include "../lib/ray.h"
#include "../texture/materials.h"

typedef struct {
    Vec3 origin;
    double radius;
    Material mat;
} Sphere;

double RayHitsSphere (Sphere s, Ray r);
Vec3 RayHitsSphere_Normal (Sphere s, Ray r, double t);

#endif //RAYTRACER_SPHERE_H