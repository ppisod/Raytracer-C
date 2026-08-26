//
// Created by JackL on 8/22/26.
//

#include "cam.h"

#include <math.h>

#include "../lib/ray.h"
#include "../utility/util.h"

double GetAspectRatio (const SceneInfo info) {
    return (double) info.ImageDimensions.x / info.ImageDimensions.y;
}

void GetBasisVectors (const Camera cam, CameraSpec *spec) {
    spec->back = vec3u(vec3sub(cam.pos, cam.looking_at)); // normalized
    spec->right = vec3u(vec3cross(UP, spec->back)); // normalized
    spec->up = vec3cross(spec->back, spec->right); // therefore normalized
}

void GetViewportSize (const SceneInfo info, const Camera cam, CameraSpec *spec) {
    const double focal_length = vec3len(vec3sub(cam.pos, cam.looking_at));
    spec->focal_length = focal_length;
    const double h = tan(Rad(cam.deg_vfov) / 2);
    const double H = 2.0 * h * focal_length;
    const double W = H * GetAspectRatio(info);
    spec->viewport = (Vec2) {W, H};
}

void GetPixelDeltas (const SceneInfo info, const Camera cam, CameraSpec *spec) {
    GetBasisVectors(cam, spec);
    spec->pixel_delta_right = vec3muls(spec->right, spec->viewport.x / info.ImageDimensions.x);
    spec->pixel_delta_down = vec3muls(spec->up, -spec->viewport.y / info.ImageDimensions.y);
}

void GetFrameVectors (const Camera cam, CameraSpec *spec) {
    spec->center = vec3sub(cam.pos, vec3muls(spec->back, spec->focal_length));
    spec->width_edge = vec3muls(spec->right, spec->viewport.x);
    spec->height_edge = vec3muls(spec->up, -spec->viewport.y);
    spec->upper_left = vec3sub(
        vec3sub(
            spec->center,
            vec3muls(spec->width_edge, 0.5)
        ),
        vec3muls(spec->height_edge, 0.5)
    );
    spec->top_left_pixel = vec3add(
        spec->upper_left,
        vec3muls(
            vec3add(spec->pixel_delta_right, spec->pixel_delta_down),
            0.5
        )
    );
}

Ray GetRayOfPixel (RenderInfo info, const Vec2 offset) {
    const Vec3 right = vec3muls(info.spec->pixel_delta_right, info.x+offset.x);
    const Vec3 down = vec3muls(info.spec->pixel_delta_down, info.y+offset.y);
    const Vec3 right_down = vec3add(right, down);
    const Vec3 pos = vec3add(info.spec->top_left_pixel, right_down);
    return (Ray) {info.cam->pos, vec3sub(pos, info.cam->pos)};
}

void Camera_DoAll (const SceneInfo info, const Camera cam, CameraSpec *spec) {
    GetViewportSize(info, cam, spec);
    GetPixelDeltas(info, cam, spec);
    GetFrameVectors(cam, spec);
}