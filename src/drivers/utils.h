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

void* memcpy(void* dest, const void* src, size_t n);

void* memset(void* dest, u_8t value, size_t n);

int strlen(char* string);

int min(int a, int b);

int max(int a, int b);

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
