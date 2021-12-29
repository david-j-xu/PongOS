#include "utils.h"

void* memcpy(void* dest, const void* src, size_t n) {
    u_8t* d = (u_8t*)dest;
    u_8t* s = (u_8t*)src;
    while (n-- > 0) {
        *d++ = *s++;
    }
    return dest;
}

void* memset(void* dest, u_8t value, size_t n) {
    u_8t* d = (u_8t*)dest;
    while (n-- > 0) {
        *d++ = value;
    }
    return dest;
}

int strlen(char* s) {
    int len = 0;
    while (*s++ != NULL) ++len;
    return len;
}

u_8t dist_decision(int x1, int y1, int x2, int y2, int d) {
    int x = x2 - x1;
    int y = y2 - y1;
    return !!(x * x + y * y <= d * d);
}

int min(int a, int b) { return a < b ? a : b; }

int max(int a, int b) { return a > b ? a : b; }

int clamp(int x, int min_x, int max_x) { return max(min(x, max_x), min_x); }

u_8t between(int x, int lo, int hi) { return (x >= lo && x <= hi); }

void cli() { __asm__ volatile("cli"); }
void sti() { __asm__ volatile("sti"); }
void halt() { __asm__ volatile("hlt"); }
