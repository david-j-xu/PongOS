/*
 *  Utility functions
 */

#pragma once

#define size_t unsigned int
#define u_8t unsigned char
#define u_16t unsigned short
#define u_32t unsigned int
#define u_64t unsigned long
#define TRUE 1
#define FALSE 0

#define NULL 0x0

/* Utility functions from standard library */

/* copies n bytes from src to dest */
void* memcpy(void* dest, const void* src, size_t n);

/* sets n bytes at dest to value */
void* memset(void* dest, u_8t value, size_t n);

/* finds length of null-terminated string */
int strlen(char* string);

/* returns min */
int min(int a, int b);

/* returns max */
int max(int a, int b);

/* clamps x between min and max */
int clamp(int x, int min, int max);

/* returns whether x is between low and high, inclusive */
u_8t between(int x, int low, int high);

/* decides whether two points are within distance d of each other */
u_8t dist_decision(int x1, int y1, int x2, int y2, int dist);

/*
 * Pause hardware interrupts
 */
void cli();

/*
 * Resume hardware interrupts
 */
void sti();

/*
 * Halts execution
 */
void halt();
