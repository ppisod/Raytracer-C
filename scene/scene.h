//
// Created by JackL on 8/22/26.
//

#ifndef RAYTRACER_SCENE_H
#define RAYTRACER_SCENE_H
#include <stdbool.h>
#include "../lib/vec3.h"
#include "../lib/ray.h"
#include "../utility/util.h"

Vec3 RayColor(int depth, const List *scene, Ray r);

#endif //RAYTRACER_SCENE_H
