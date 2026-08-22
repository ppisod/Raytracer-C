//
// Created by JackL on 8/21/26.
//

#ifndef RAYTRACER_VEC2_H
#define RAYTRACER_VEC2_H

typedef struct {
    double x, y;
} Vec2;

/* lib/vec2.c */
Vec2 vec2add(Vec2 a, Vec2 b);
Vec2 vec2sub(Vec2 a, Vec2 b);
Vec2 vec2eq(Vec2 a, Vec2 b);
Vec2 vec2eq_norm(Vec2 a, Vec2 b, double eps);
Vec2 vec2muls(Vec2 a, double s);
Vec2 vec2mul(Vec2 a, Vec2 b);
Vec2 vec2divs(Vec2 a, double s);
Vec2 vec2div(Vec2 a, Vec2 b);
double vec2dot(Vec2 a, Vec2 b);
double vec2len(Vec2 a);
double vec2lensqrd(Vec2 a);
Vec2 vec2u(Vec2 a);
void vec2u_inplace(Vec2 *a);

#endif //RAYTRACER_VEC2_H