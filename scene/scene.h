//
// Created by JackL on 8/22/26.
//

#ifndef RAYTRACER_SCENE_H
#define RAYTRACER_SCENE_H
#include <stdbool.h>

#include "../lib/vec3.h"
#include "../lib/vec2.h"
#include "../lib/ray.h"
#include "../shape/sphere.h"
#include "../utility/util.h"
#include "../lib/pixel.h"

typedef struct {
    bool Hit;
    double T;
    Vec3 HitPoint;
    Vec3 SurfaceNormal;
} HitResult;

typedef struct {
    Vec2 ImageDimensions;
    int AntiAliasSamples;
} SceneInfo;

Vec3 RayColor(int depth, List scene, Ray r);

#endif //RAYTRACER_SCENE_H
