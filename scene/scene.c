//
// Created by JackL on 8/22/26.
//

#include "scene.h"
#include "../lib/ray.h"
#include "../lib/pixel.h"
#include "../shape/sphere.h"
#include "../utility/util.h"
#include <math.h>

#include <stdlib.h>

const Vec3 WHITE = {1, 1, 1};
const Vec3 SKY = {0.5, 0.7, 1.0};
const Vec3 GRAY = {0.7, 0.7, 0.7};
const Vec3 BLACK = {0, 0, 0};

HitResult HitScene (const List scene, Ray r) {
    HitResult best;
    best.Hit = false;
    best.T = INFINITY;
    best.SurfaceNormal = (Vec3) {0, 0, 0};
    best.HitPoint = (Vec3) {0, 0, 0};
    for (int i = 0; i < scene.len; i++) {
        const Sphere s = *(Sphere*) GetListElement_Ptr(scene, i);
        const double T = RayHitsSphere(s, r);
        if (T > 0 && T < best.T) {
            best.Hit = true;
            best.T = T;
            best.HitPoint = vec3add(r.origin, vec3muls(r.direction, T));
            best.SurfaceNormal = RayHitsSphere_Normal(s, r, T);
        }
    }

    return best;
}

Vec3 RayColor (const List scene, const Ray r) {
    const Vec3 unit = vec3u(r.direction);
    const double Vert = 0.5*(unit.y+1);

    const HitResult result = HitScene(scene, r);
    if (result.Hit == true) {
        return vec3muls(vec3add(result.SurfaceNormal, WHITE), 0.5);
    }

    if (Vert < 0.45) {
        return WHITE;
    }

    if (Vert <= 0.55) {
        const double k = (Vert-0.45)/0.1;
        return vec3add(vec3muls(WHITE, 1-k), vec3muls(SKY, k));
    }

    return SKY;
}