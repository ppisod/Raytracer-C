//
// Created by JackL on 8/19/26.
//

#ifndef RAYTRACER_VEC3_H
#define RAYTRACER_VEC3_H
typedef struct {
    double x, y, z;
} Vec3;
static const Vec3 UP;
/* lib/vec3.c */
void vec3print(char name[], Vec3 vec);
Vec3 vec3add(Vec3 a, Vec3 b);
Vec3 vec3sub(Vec3 a, Vec3 b);
Vec3 vec3eq(Vec3 a, Vec3 b);
Vec3 vec3eq_norm(Vec3 a, Vec3 b, double eps);
Vec3 vec3muls(Vec3 a, double s);
Vec3 vec3mul(Vec3 a, Vec3 b);
Vec3 vec3divs(Vec3 a, double s);
Vec3 vec3div(Vec3 a, Vec3 b);
double vec3dot(Vec3 a, Vec3 b);
Vec3 vec3cross(Vec3 a, Vec3 b);
double vec3len(Vec3 a);
double vec3lensqrd(Vec3 a);
Vec3 vec3u(Vec3 a);
Vec3 vec3max (Vec3 a, Vec3 b);
Vec3 vec3min (Vec3 a, Vec3 b);
void vec3u_inplace(Vec3 *a);
#endif //RAYTRACER_VEC3_H