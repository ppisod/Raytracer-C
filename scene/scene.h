//
// Created by JackL on 8/22/26.
//

#ifndef RAYTRACER_SCENE_H
#define RAYTRACER_SCENE_H
#include <stdbool.h>
#include "../lib/vec3.h"
#include "../lib/vec2.h"

typedef struct {
    bool Hit;
    double T;
    Vec3 HitPoint;
    Vec3 SurfaceNormal;
} HitResult;

typedef struct {
    Vec2 ImageDimensions;
} SceneInfo;

#endif //RAYTRACER_SCENE_H