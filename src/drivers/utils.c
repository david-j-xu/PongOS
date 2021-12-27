#include "utils.h"

void* memcpy(void* dest, const void* src, size_t n) {
    u_8t* d = (u_8t*)dest;
    u_8t* s = (u_8t*)src;
    while (n > 0) {
        *d = *s;
        --n;
        ++d;
        ++s;
    }
    return dest;
}

void* memset(void* dest, u_8t value, size_t n) {
    u_8t* d = (u_8t*)dest;
    while (n > 0) {
        *d = value;
        --n;
        ++d;
    }
    return dest;
}