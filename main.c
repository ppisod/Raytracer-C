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
    const Camera cam = (Camera) {(Vec3) {0.7, 0.7, 0.7}, (Vec3) {0, 0, 0}, 120};
    CameraSpec spec = (CameraSpec) {0};
    const SceneInfo info = (SceneInfo) {(Vec2) {Width, Height}, 40};
    Camera_DoAll(info, cam, &spec);

    Sphere spheres[] = {
        (Sphere) {{0, 0, 0}, 0.5},
        (Sphere) {{0, -105, 0}, 100}
    };

    const List list = {
        spheres,
        sizeof(spheres[0]),
        sizeof(spheres)/sizeof(spheres[0])
    };

    return WriteFile(info, list, cam, &spec);
}