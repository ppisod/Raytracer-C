//
// Created by JackL on 8/23/26.
//

#ifndef RAYTRACER_UTIL_H
#define RAYTRACER_UTIL_H
#include <stdint.h>

typedef struct {
    void* data;
    int len_per_el;
    int len;
} List;

static const double PI = 3.14159265358979323846264338327950288;
double RandomDouble(void);
void SeedRng (uint64_t s);
static uint64_t SplitMix64 (uint64_t x) {
    x += 0x9E3779B97F4A7C15ULL;
    x = (x ^ (x >> 30)) * 0xBF58476D1CE4E5B9ULL;
    x = (x ^ (x >> 27)) * 0x94D049BB133111EBULL;
    return x ^ (x >> 31);
}

double Rad(double Deg);

char* GetListElement_Ptr (List l, int idx);
char* GetPtrListElement_Ptr (const List *l, int idx);

#endif //RAYTRACER_UTIL_H