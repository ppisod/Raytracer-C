//
// Created by JackL on 8/24/26.
//

#include "plane.h"
#include "../lib/ray.h"
#include <math.h>

double RayHitsPlane (const Plane p, const Ray r) {

    // for some position vector P
    // for some other position vector Q, established on the
    // plane's surface (i.e., the origin position of the plane)
    // P is on the surface if the vector Q to P is perpendicular
    // to the normal vector of the plane.

    // Two vectors are perpendicular if their dot is zero.
    // such that: (P-Q) dot N = 0
    // A ray's position vector is O + tD for O origin, D direction, t time
    // Let P = O + tD = R
    // (O+tD-Q) dot N = 0
    // we can group up O, Q to be K = O-Q
    // (K+tD) dot N = 0
    // The dot operator can distribute over addition:
    // (K dot N) + t(D dot N) = 0
    // t(D dot N) = - (K dot N)
    // [1]: t = -(K dot N) / (D dot N)

    // we can find the length of vector P - Q, that is the distance.

    const double denom = vec3dot(r.direction, p.normal);
    if (fabs(denom) < 1e-8) {
        return -1;
    }
    const double num = -1 * vec3dot(vec3sub(r.origin, p.origin), p.normal);

    const double t = num/denom;

    // calculate point
    const Vec3 point = vec3add(r.origin, vec3muls(r.direction, t));
    const double len = vec3lensqrd(vec3sub(point, p.origin));

    if (len > p.rad) {
        return -1;
    }

    return num/denom;

}

Vec3 RayHitsPlane_Normal (const Plane p) {
    return p.normal;
}