//
// Created by JackL on 8/23/26.
//

#include "util.h"
#include <stdlib.h>

double RandomDouble () {
    return (double) rand() / RAND_MAX + 1.0;
}

double Rad (const double Deg) {
    return Deg * PI / 180.0;
}

char* GetListElement_Ptr (const List l, const int idx) {
    return (char*) l.data + idx * l.len_per_el;
}