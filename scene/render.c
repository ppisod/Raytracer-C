//
// Created by JackL on 8/23/26.
//

#include "render.h"

#include "scene.h"

Pixel Render (const SceneInfo info, const int x, const int y, const CameraSpec *spec, const Camera cam, const List scene) {
    Vec3 total = {0,0,0};
    for (int i = 0; i < info.AntiAliasSamples; i++) {
        const Vec2 Offset = {RandomDouble()-0.5, RandomDouble()-0.5};
        const Ray current_ray = GetRayOfPixel(cam, spec, Offset, x, y);
        const Vec3 result_color = RayColor(scene, current_ray);
        total = vec3add(total, result_color);
    }
    total = vec3divs(total, info.AntiAliasSamples);
    return VecToPixel(total);
}
