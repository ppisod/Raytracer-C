//
// Created by JackL on 8/25/26.
//

#ifndef RAYTRACER_THREAD_MAIN_H
#define RAYTRACER_THREAD_MAIN_H

#include "../scene/scene_types.h"

int WriteFile (int threads, int w, int h, int depth, SceneInfo info, const List *scene, Camera cam, CameraSpec *spec);

#endif //RAYTRACER_THREAD_MAIN_H