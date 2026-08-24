#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#include "lib/pixel.h"
#include "lib/ray.h"
#include "lib/vec3.h"
#include "lib/vec2.h"
#include "scene/cam.h"
#include "scene/render.h"
#include "scene/scene.h"
#include "shape/shape.h"
#include "shape/sphere.h"
#include "utility/util.h"

static const int Width = 600;
static const int Height = 400;

Pixel DefaultImage_GetPixel (const int x, const int y, const int w, const int h) {
    const double x_norm = (double) x / (double) w;
    const double y_norm = (double) y / (double) h;

    return (Pixel) {(unsigned char)(x_norm*255), (unsigned char)(y_norm*255), 120};
}

// Main functions
int WriteFile (const SceneInfo info, const List scene, const Camera cam, CameraSpec *spec) {

    FILE *f = fopen ("out.ppm", "w");
    if (!f) {perror("fopen failed"); return 1;}

    fprintf(f, "P3\n%d %d\n255\n", Width, Height);

    for (int y = 0; y < Height; y++) {
        for (int x = 0; x < Width; x++) {
            const Pixel p = Render(info, x, y, spec, cam, scene);
            fprintf(f, "%d %d %d \n", p.r, p.g, p.b);
        }
    }

    fclose(f);

    return 0;
}

int main(void) {
    const Camera cam = (Camera) {(Vec3) {0.7, 0.7, 0.7}, (Vec3) {0, 0, 0}, 90};
    CameraSpec spec = (CameraSpec) {0};
    const SceneInfo info = (SceneInfo) {(Vec2) {Width, Height}, 40};
    Camera_DoAll(info, cam, &spec);

    Material albert = {Mat_Lambertian, {0.6, 0.7, 0.9}, 0};
    Material metal = {Mat_Metal, {0.8, 0.8, 0.8}, 0.25};


    Shape scene[] = {
        (Shape) {.type=Shape_Sphere, .mat=albert, .sphere=(Sphere) {{0, 0, 0}, 0.5}},
        (Shape) {.type=Shape_Sphere, .mat=metal, .sphere=(Sphere) {{1, -3, 0}, 3}},
        (Shape) {.type=Shape_Sphere, .mat=albert, .sphere=(Sphere) {{0, -105, 0}, 100}},
        (Shape) {.type=Shape_Plane, .mat=metal, .plane=(Plane) {{0, 0, 0}, {0.7, 1.4, 1}, 0.9}}
    };

    const List list = {
        scene,
        sizeof(scene[0]),
        sizeof(scene)/sizeof(scene[0])
    };

    return WriteFile(info, list, cam, &spec);
}