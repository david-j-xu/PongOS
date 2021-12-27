#pragma once

#define size_t unsigned int
#define u_8t unsigned char
#define u_16t unsigned short
#define u_32t unsigned int

#define NULL 0x0

/* Utility functions from standard library */

void* memcpy(void* dest, const void* src, size_t n);

void* memset(void* dest, u_8t value, size_t n);