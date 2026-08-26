//
// Created by JackL on 8/22/26.
//

#ifndef RAYTRACER_CAM_H
#define RAYTRACER_CAM_H

#include "scene.h"
#include "../lib/vec3.h"
#include "../lib/vec2.h"
#include "../lib/ray.h"
#include "scene_types.h"

double GetAspectRatio(SceneInfo info);
void GetBasisVectors(Camera cam, CameraSpec *spec);
void GetViewportSize(SceneInfo info, Camera cam, CameraSpec *spec);
void GetPixelDeltas(SceneInfo info, Camera cam, CameraSpec *spec);
void GetFrameVectors(Camera cam, CameraSpec *spec);
void Camera_DoAll(SceneInfo info, Camera cam, CameraSpec *spec);

Ray GetRayOfPixel (RenderInfo info, Vec2 offset);

#endif //RAYTRACER_CAM_H