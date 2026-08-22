//
// Created by JackL on 8/22/26.
//
#include <tgmath.h>

#include "../lib/vec3.h"
#include "../lib/ray.h"
#include "sphere.h"

double SolveQuadratic_SmallestSolution (const double A, const double B, const double C) {
    const double disc = B*B - 4*A*C;
    const double sol_1 = (-B + sqrt(disc)) / (2*A);
    const double sol_2 = (-B - sqrt(disc)) / (2*A);
    if (sol_1 > sol_2) return sol_2;
    return sol_1;
}

double RayHitsSphere (const Sphere s, const Ray r) {
    const Vec3 K = vec3sub(r.origin, s.origin);
    const double Coeff_A = vec3dot(r.direction, r.direction);
    const double Coeff_B = 2 * vec3dot(K, r.direction);
    const double Coeff_C = vec3dot(K, K) - s.radius * s.radius;
    const double discriminant = Coeff_B*Coeff_B - 4*Coeff_A*Coeff_C;
    if (discriminant < 0) return -1;
    const double t = SolveQuadratic_SmallestSolution(Coeff_A, Coeff_B, Coeff_C);
    if (t < 0) return -1;
    return t;
}