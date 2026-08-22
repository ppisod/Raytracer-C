//
// Created by JackL on 8/22/26.
//

#ifndef RAYTRACER_CAM_H
#define RAYTRACER_CAM_H

#include "scene.h"
#include "../lib/vec3.h"
#include "../lib/vec2.h"
#include "../lib/ray.h"

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

double Rad(double Deg);
double GetAspectRatio(SceneInfo info);
void GetBasisVectors(SceneInfo info, Camera cam, CameraSpec *spec);
void GetViewportSize(SceneInfo info, Camera cam, CameraSpec *spec);
void GetPixelDeltas(SceneInfo info, Camera cam, CameraSpec *spec);
void GetFrameVectors(Camera cam, CameraSpec *spec);
void Camera_DoAll(SceneInfo info, Camera cam, CameraSpec *spec);
Ray GetRayOfPixel (Camera cam, const CameraSpec *spec, int pixel_X, int pixel_Y);

#endif //RAYTRACER_CAM_H