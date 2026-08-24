//
// Created by JackL on 8/19/26.
//

#include <math.h>
#include "vec3.h"
#include "../utility/util.h"

#include <stdio.h>

void vec3print (char name[], Vec3 vec) {
    printf("%s: {%f, %f, %f} \n", name, vec.x, vec.y, vec.z);
}

Vec3 vec3add (const Vec3 a, const Vec3 b) {
    return (Vec3) {a.x + b.x, a.y + b.y, a.z + b.z};
}

Vec3 vec3sub (const Vec3 a, const Vec3 b) {
    return (Vec3) {a.x - b.x, a.y - b.y, a.z - b.z};
}

Vec3 vec3eq (const Vec3 a, const Vec3 b) {
    return (Vec3) {a.x == b.x, a.y == b.y, a.z == b.z};
}

Vec3 vec3eq_norm (const Vec3 a, const Vec3 b, const double eps) {
    return (Vec3) {fabs(a.x - b.x) < eps, fabs(a.y - b.y) < eps, fabs(a.z - b.z) < eps};
}

Vec3 vec3muls (const Vec3 a, const double s) {
    return (Vec3) {a.x * s, a.y * s, a.z * s};
}

Vec3 vec3mul (const Vec3 a, const Vec3 b) {
    return (Vec3) {a.x * b.x, a.y * b.y, a.z * b.z};
}

Vec3 vec3divs (const Vec3 a, const double s) {
    return (Vec3) {a.x / s, a.y / s, a.z / s};
}

Vec3 vec3div (const Vec3 a, const Vec3 b) {
    return (Vec3) {a.x / b.x, a.y / b.y, a.z / b.z};
}

double vec3dot (const Vec3 a, const Vec3 b) {
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

Vec3 vec3cross (const Vec3 a, const Vec3 b) {
    return (Vec3) {
        (a.y * b.z) - (a.z * b.y),
        (a.z * b.x) - (a.x * b.z),
        (a.x * b.y) - (a.y * b.x)
    };
}

double vec3len (const Vec3 a) {
    return sqrt(pow(a.x, 2)+pow(a.y, 2)+pow(a.z, 2));
}

double vec3lensqrd (const Vec3 a) {
    return pow(a.x, 2)+pow(a.y, 2)+pow(a.z, 2);
}

Vec3 vec3u (const Vec3 a) {
    const double len = vec3len(a);
    if (len == 0) return a;
    return (Vec3) {a.x/len, a.y/len, a.z/len};
}

Vec3 vec3max (const Vec3 a, const Vec3 b) {
    if (vec3lensqrd(a) > vec3lensqrd(b)) return a;
    return b;
}

Vec3 vec3min (const Vec3 a, const Vec3 b) {
    if (vec3lensqrd(a) < vec3lensqrd(b)) return a;
    return b;
}

void vec3u_inplace (Vec3 *a) {
    Vec3 b = *a;
    const double len = vec3len(b);
    if (len == 0) return;
    a->x /= len;
    a->y /= len;
    a->z /= len;
}

Vec3 vec3rand (void) {
    loop: ;
        const Vec3 p = (Vec3) {2*RandomDouble()-1, 2*RandomDouble()-1, 2*RandomDouble()-1};
        const double len = vec3lensqrd(p);
        if (len > 1e-160 && len <= 1.0) {
            return vec3divs(p, sqrt(len));
        }
        goto loop;
}

Vec3 vec3reflect (const Vec3 incident, const Vec3 normal, const double factor) {
    return vec3sub(incident, vec3muls(vec3muls(normal, vec3dot(incident, normal)), factor));
}
