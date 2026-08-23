//
// Created by JackL on 8/23/26.
//

#ifndef RAYTRACER_RENDER_H
#define RAYTRACER_RENDER_H
#include "cam.h"

Pixel Render(SceneInfo info, int x, int y, const CameraSpec *spec, Camera cam, List scene);

#endif //RAYTRACER_RENDER_H