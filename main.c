#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#include "lib/ray.h"
#include "lib/vec3.h"
#include "lib/vec2.h"
#include "scene/cam.h"
#include "shape/sphere.h"

typedef struct {
    unsigned char r, g, b;
} Pixel;

static const int Width = 600;
static const int Height = 400;

const Vec3 WHITE = {1, 1, 1};
const Vec3 SKY = {0.5, 0.7, 1.0};
const Vec3 GRAY = {0.7, 0.7, 0.7};
const Vec3 BLACK = {0, 0, 0};

Pixel DefaultImage_GetPixel (const int x, const int y, const int w, const int h) {
    const double x_norm = (double) x / (double) w;
    const double y_norm = (double) y / (double) h;

    return (Pixel) {(unsigned char)(x_norm*255), (unsigned char)(y_norm*255), 120};
}
// Ray utilities
Ray GetRayOfPixel (const Camera cam, const CameraSpec *spec, const int pixel_X, const int pixel_Y) {
    const Vec3 right = vec3muls(spec->pixel_delta_right, pixel_X);
    const Vec3 down = vec3muls(spec->pixel_delta_down, pixel_Y);
    const Vec3 offset = vec3add(right, down);
    const Vec3 pixel_center = vec3add(spec->top_left_pixel, offset);
    return (Ray) {cam.pos, vec3sub(pixel_center, cam.pos)};
}

Vec3 RayColor (const Ray r) {
    const Vec3 unit = vec3u(r.direction);
    const double Vert = 0.5*(unit.y+1);
    // from 0.45-0.55, display band of sky gradient
    // so if Vert < 0.45, White,
    // if 0.45 <= Vert <= 0.55, k = ((Vert - 0.45) / 0.1), White * (1-k) + Sky * k
    // else Vert > 0.45, Sky

    const Sphere s = {(Vec3) {0, 0, 0}, 0.5};
    const double T = RayHitsSphere(s, r);
    if (T > 0) {
        Vec3 normal = RayHitsSphere_Normal(s, r, T);
        const Vec3 col = vec3muls(vec3add(normal, WHITE), 0.5);
        return col;
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

Pixel VecToPixel (const Vec3 color) {
    return (Pixel)
        {
            (unsigned char) (color.x * 255.999),
            (unsigned char) (color.y * 255.999),
            (unsigned char) (color.z * 255.999)
        };
}

// Main functions
int WriteFile (const Camera cam, const CameraSpec *spec) {

    FILE *f = fopen ("out.ppm", "w");
    if (!f) {perror("fopen failed"); return 1;}

    fprintf(f, "P3\n%d %d\n255\n", Width, Height);

    for (int y = 0; y < Height; y++) {
        for (int x = 0; x < Width; x++) {
            const Ray current_ray = GetRayOfPixel(cam, spec, x, y);
            const Vec3 result_color = RayColor(current_ray);
            Pixel as_pixel = VecToPixel(result_color);
            fprintf(f, "%d %d %d \n", as_pixel.r, as_pixel.g, as_pixel.b);
        }
    }

    fclose(f);

    return 0;
}

int main(void) {
    const Camera cam = (Camera) {(Vec3) {0.7, 0.7, 0.7}, (Vec3) {0, 0, 0}, 120};
    CameraSpec spec = (CameraSpec) {0};
    const SceneInfo info = (SceneInfo) {(Vec2) {Width, Height}};
    Camera_DoAll(info, cam, &spec);

    return WriteFile(cam, &spec);
}