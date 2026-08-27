//
// Created by JackL on 8/23/26.
//

#include "util.h"
#include <stdlib.h>

static _Thread_local uint64_t rng_state = 0;

void SeedRng (const uint64_t s) {
    rng_state = SplitMix64(s);
}

double RandomDouble (void) {
    rng_state ^= rng_state << 13;
    rng_state ^= rng_state >> 7;
    rng_state ^= rng_state << 17;
    return (rng_state >> 11) * 0x1.0p-53;
}

double Rad (const double Deg) {
    return Deg * PI / 180.0;
}

char* GetListElement_Ptr (const List l, const int idx) {
    return (char*) l.data + idx * l.len_per_el;
}

char* GetPtrListElement_Ptr (const List *l, const int idx) {
    return (char*) l->data + idx * l->len_per_el;
}