//
// Created by JackL on 8/24/26.
//

#ifndef RAYTRACER_SHAPE_H
#define RAYTRACER_SHAPE_H

#include "plane.h"
#include "sphere.h"
#include "../texture/materials.h"

typedef enum {
    Shape_Sphere, Shape_Plane
} ShapeType;

typedef struct {
    ShapeType type;
    Material mat;
    union {
        Sphere sphere;
        Plane plane;
    };
} Shape;

#endif //RAYTRACER_SHAPE_H