//
// Created by JackL on 8/24/26.
//

#ifndef RAYTRACER_PLANE_H
#define RAYTRACER_PLANE_H

#include "../lib/vec3.h"
#include "../lib/ray.h"

typedef struct {
    Vec3 origin;
    Vec3 normal;
    double rad;
} Plane;

double RayHitsPlane(Plane p, Ray r);
Vec3 RayHitsPlane_Normal(Plane p);

#endif //RAYTRACER_PLANE_H