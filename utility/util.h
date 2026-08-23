//
// Created by JackL on 8/23/26.
//

#ifndef RAYTRACER_UTIL_H
#define RAYTRACER_UTIL_H

typedef struct {
    void* data;
    int len_per_el;
    int len;
} List;

static const double PI = 3.14159265358979323846264338327950288;
double RandomDouble(void);
double Rad(double Deg);

char* GetListElement_Ptr (List l, int idx);

#endif //RAYTRACER_UTIL_H