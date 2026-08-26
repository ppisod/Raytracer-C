//
// Created by JackL on 8/26/26.
//

#ifndef RAYTRACER_SCENE_TYPES_H
#define RAYTRACER_SCENE_TYPES_H
#include <stdbool.h>
#include "../lib/vec3.h"
#include "../lib/vec2.h"
#include "../utility/util.h"
#include "../lib/ray.h"
#include "../texture/materials.h"

typedef struct {
    bool Hit;
    double T;
    Vec3 HitPoint;
    Vec3 SurfaceNormal;
    Material Material;
    Ray Ray;
} HitResult;

typedef struct {
    Vec2 ImageDimensions;
    int AntiAliasSamples;
} SceneInfo;


typedef struct {
    Vec3 pos;
    Vec3 looking_at;
    double deg_vfov;
} Camera;

typedef struct {
    double focal_length;
    Vec2 viewport;

    Vec3 back, right, up;
    Vec3 pixel_delta_right, pixel_delta_down;

    Vec3 upper_left;
    Vec3 top_left_pixel;

    Vec3 center;

    Vec3 width_edge;
    Vec3 height_edge;
} CameraSpec;

typedef struct {
    const int x, y;
    const SceneInfo *info;
    const List *scene;
    const Camera *cam;
    const CameraSpec *spec;
} RenderInfo;

#endif //RAYTRACER_SCENE_TYPES_H