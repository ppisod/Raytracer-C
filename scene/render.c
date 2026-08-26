//
// Created by JackL on 8/23/26.
//

#include "render.h"

#include "cam.h"
#include "scene.h"


Pixel Render (const RenderInfo info) {
    Vec3 total = {0,0,0};
    for (int i = 0; i < info.info->AntiAliasSamples; i++) {
        const Vec2 Offset = {RandomDouble()-0.5, RandomDouble()-0.5};
        const Ray current_ray = GetRayOfPixel(info, Offset);
        const Vec3 result_color = RayColor(6, info.scene, current_ray);
        total = vec3add(total, result_color);
    }
    total = vec3divs(total, info.info->AntiAliasSamples);
    return VecToPixel(total);
}
