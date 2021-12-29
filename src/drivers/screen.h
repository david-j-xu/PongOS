/*
 * Device driver for a VGA display
 */

#pragma once
#include "io.h"
#include "utils.h"

#define SCREEN_HEIGHT 200
#define SCREEN_WIDTH 320
#define SCREEN_SIZE ((SCREEN_HEIGHT) * (SCREEN_WIDTH))
/* VGA control addresses */
#define VGA_PALETTE_MASK 0x3C6
#define VGA_CONTROL_READ 0x3C7
#define VGA_CONTROL_WRITE 0x3C8
#define VGA_CONTROL_DATA 0x3C9

#define COLOR(r, g, b) ((u_8t)((((r)&7) << 5) | (((g)&7) << 2) | (((b)&3))))

#define WHITE COLOR(7, 7, 3)
#define BLACK COLOR(0, 0, 0)

static unsigned char* VGA_BUFFER = (u_8t*)0xA0000;

/*
 * Initializes the screen and palette
 */
void init_screen();

/*
 * Clears the screen with the designated color
 */
void clear_screen(u_8t color);

/*
 * Sets a pixel of the current buffer
 */
void set_pixel(u_16t x, u_16t y, u_8t color);

/*
 * Draws a rectangle at (x, y) with width w and height h
 */
void draw_rectangle(u_16t x, u_16t y, u_16t w, u_16t h, u_8t color);

/*
 * Draws a rectangle at (x, y) with width w and height h in rainbow
 */
void draw_rectangle_r(u_16t x, u_16t y, u_16t w, u_16t h);

/*
 * Draws a circle with center (x, y) with radius r
 */
void draw_circle(u_16t x, u_16t y, u_16t r, u_8t color);

/*
 * Draws a circle with center (x, y) with radius r, in rainbow!
 */
void draw_circle_r(u_16t x, u_16t y, u_16t r);

/*
 * Draws the current buffer
 */
void draw();
