//
// Created by JackL on 8/20/26.
//

#include <math.h>
#include "vec2.h"

Vec2 vec2add (const Vec2 a, const Vec2 b) {
    return (Vec2) {a.x + b.x, a.y + b.y};
}

Vec2 vec2sub (const Vec2 a, const Vec2 b) {
    return (Vec2) {a.x - b.x, a.y - b.y};
}

Vec2 vec2eq (const Vec2 a, const Vec2 b) {
    return (Vec2) {a.x == b.x, a.y == b.y};
}

Vec2 vec2eq_norm (const Vec2 a, const Vec2 b, const double eps) {
    return (Vec2) {fabs(a.x - b.x) < eps, fabs(a.y - b.y) < eps};
}

Vec2 vec2muls (const Vec2 a, const double s) {
    return (Vec2) {a.x * s, a.y * s};
}

Vec2 vec2mul (const Vec2 a, const Vec2 b) {
    return (Vec2) {a.x * b.x, a.y * b.y};
}

Vec2 vec2divs (const Vec2 a, const double s) {
    return (Vec2) {a.x / s, a.y / s};
}

Vec2 vec2div (const Vec2 a, const Vec2 b) {
    return (Vec2) {a.x / b.x, a.y / b.y};
}

double vec2dot (const Vec2 a, const Vec2 b) {
    return a.x*b.x + a.y*b.y;
}

double vec2len (const Vec2 a) {
    return sqrt(pow(a.x, 2)+pow(a.y, 2));
}

double vec2lensqrd (const Vec2 a) {
    return pow(a.x, 2)+pow(a.y, 2);
}

Vec2 vec2u (const Vec2 a) {
    const double len = vec2len(a);
    if (len == 0) return a;
    return (Vec2) {a.x/len, a.y/len};
}

void vec2u_inplace (Vec2 *a) {
    Vec2 b = *a;
    const double len = vec2len(b);
    if (len == 0) return;
    a->x /= len;
    a->y /= len;
}