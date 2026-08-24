//
// Created by JackL on 8/22/26.
//

#include "scene.h"
#include "../lib/ray.h"
#include "../lib/pixel.h"
#include "../shape/shape.h"
#include "../utility/util.h"
#include <math.h>

#include <stdlib.h>

const Vec3 WHITE = {1, 1, 1};
const Vec3 SKY = {0.5, 0.7, 1.0};
const Vec3 GRAY = {0.7, 0.7, 0.7};
const Vec3 BLACK = {0, 0, 0};

HitResult HitScene (const List scene, const Ray r) {
    HitResult best;
    best.Hit = false;
    best.T = INFINITY;
    best.SurfaceNormal = (Vec3) {0, 0, 0};
    best.HitPoint = (Vec3) {0, 0, 0};
    best.Material = (Material) {Mat_Lambertian, {0, 0, 0}, 0};
    best.Ray = r;
    for (int i = 0; i < scene.len; i++) {
        const Shape s = *(Shape*) GetListElement_Ptr(scene, i);
        double T = 0;

        switch (s.type) {
            case Shape_Sphere: ;
                T = RayHitsSphere(s.sphere, r);
                break;
            case Shape_Plane: ;
                T = RayHitsPlane(s.plane, r);
                break;
        }
        if (T > 0 && T < best.T) {
            best.Hit = true;
            best.T = T;
            best.HitPoint = vec3add(r.origin, vec3muls(r.direction, T));

            switch (s.type) {
                case Shape_Sphere: ;
                    best.SurfaceNormal = RayHitsSphere_Normal(s.sphere, r, T);
                    break;
                case Shape_Plane: ;
                    best.SurfaceNormal = RayHitsPlane_Normal(s.plane);
                    break;
            }

            best.Material = s.mat;
        }
    }

    return best;
}

Vec3 RayColor (const int depth, const List scene, const Ray r) {
    const Vec3 unit = vec3u(r.direction);
    const double Vert = 0.5*(unit.y+1);

    if (depth <= 0) {
        return BLACK;
    }

    const HitResult result = HitScene(scene, r);

    if (result.Hit == true) {
        switch (result.Material.type) {
            case Mat_Lambertian: ;
                Vec3 dir = vec3add(result.SurfaceNormal, vec3rand());
                Ray bounced = {result.HitPoint, dir};
                return vec3mul(RayColor(depth - 1, scene, bounced), result.Material.albedo);
            case Mat_Metal: ;
                dir = vec3reflect(result.Ray.direction, result.SurfaceNormal, 2);
                bounced = (Ray) {result.HitPoint, dir};
                return vec3muls(RayColor(depth - 1, scene, bounced), 1-result.Material.fuzz);
            default: ;
                return BLACK;
        }
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