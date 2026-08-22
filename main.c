#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#include "lib/ray.h"
#include "lib/vec3.h"
#include "lib/vec2.h"

typedef struct {
    unsigned char r, g, b;
} Pixel;

typedef struct {
    Vec3 pos;
    Vec3 looking_at;
    double deg_vfov;
} Camera;

typedef struct {
    double focal_length;
    Vec2 viewport;

    Vec3 back, right, up;
    Vec3 pixel_delta_right, pixel_delta_down;

    Vec3 upper_left;
    Vec3 top_left_pixel;

    Vec3 center;

    Vec3 width_edge;
    Vec3 height_edge;
} CameraSpec;

static const int Width = 600;
static const int Height = 400;

static const Vec3 UP = (Vec3) {0, 1, 0};
static const double PI = 3.14159265358979323846264338327950288;

const Vec3 WHITE = {1, 1, 1};
const Vec3 SKY = {0.5, 0.7, 1.0};
const Vec3 GRAY = {0.7, 0.7, 0.7};
const Vec3 BLACK = {0, 0, 0};

double Rad (const double Deg) {
    return Deg * PI / 180.0;
}

double GetAspectRatio () {
    return (double) Width / Height;
}

Pixel DefaultImage_GetPixel (const int x, const int y, const int w, const int h) {
    const double x_norm = (double) x / (double) w;
    const double y_norm = (double) y / (double) h;

    return (Pixel) {(unsigned char)(x_norm*255), (unsigned char)(y_norm*255), 120};
}


// Functions initializing the camera, and the camera spec
void GetBasisVectors (const Camera cam, CameraSpec *spec) {
    spec->back = vec3u(vec3sub(cam.pos, cam.looking_at)); // normalized
    spec->right = vec3u(vec3cross(UP, spec->back)); // normalized
    spec->up = vec3cross(spec->back, spec->right); // therefore normalized
}

void GetViewportSize (const Camera cam, CameraSpec *spec) {
    const double focal_length = vec3len(vec3sub(cam.pos, cam.looking_at));
    spec->focal_length = focal_length;
    const double h = tan(Rad(cam.deg_vfov) / 2);
    const double H = 2.0 * h * focal_length;
    const double W = H * GetAspectRatio();
    spec->viewport = (Vec2) {W, H};
}

void GetPixelDeltas (const Camera cam, CameraSpec *spec) {
    GetBasisVectors(cam, spec);
    spec->pixel_delta_right = vec3muls(spec->right, spec->viewport.x / Width);
    spec->pixel_delta_down = vec3muls(spec->up, -spec->viewport.y / Height);
}

void GetFrameVectors (const Camera cam, CameraSpec *spec) {
    spec->center = vec3sub(cam.pos, vec3muls(spec->back, spec->focal_length));
    spec->width_edge = vec3muls(spec->right, spec->viewport.x);
    spec->height_edge = vec3muls(spec->up, -spec->viewport.y);
    spec->upper_left = vec3sub(
        vec3sub(
            spec->center,
            vec3muls(spec->width_edge, 0.5)
        ),
        vec3muls(spec->height_edge, 0.5)
    );
    spec->top_left_pixel = vec3add(
        spec->upper_left,
        vec3muls(
            vec3add(spec->pixel_delta_right, spec->pixel_delta_down),
            0.5
        )
    );
}

void Camera_DoAll (const Camera cam, CameraSpec *spec) {
    GetViewportSize(cam, spec);
    GetPixelDeltas(cam, spec);
    GetFrameVectors(cam, spec);
}

// Debug print functions
void PrintBasisVectors (const CameraSpec *spec) {
    vec3print("back", spec->back);
    vec3print("right", spec->right);
    vec3print("up", spec->up);
}

void PrintViewportSize (const CameraSpec *spec) {
    printf("width: %f\n", spec->viewport.x);
    printf("height: %f\n", spec->viewport.y);
}

void PrintPixelDeltas (const CameraSpec *spec) {
    vec3print("pd_right", spec->pixel_delta_right);
    vec3print("pd_down", spec->pixel_delta_down);
}

void PrintFrameVectors (const CameraSpec *spec) {
    vec3print("center", spec->center);
    vec3print("upper_left", spec->upper_left);
    vec3print("top_left_pixel", spec->top_left_pixel);
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
    double HitResult = HitsSphere(s, r);
    if (HitResult != -1) {
        if (HitResult > 1) HitResult = 1;
        const Vec3 col = vec3add(vec3muls(GRAY, 1 - HitResult), vec3muls(BLACK, HitResult));
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
    Camera_DoAll(cam, &spec);

    return WriteFile(cam, &spec);
}