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

static unsigned char* VGA_BUFFER = (unsigned char*)0xA0000;

/*
 * Initializes the screen and palette
 */
void init_screen();

/*
 * Clears the screen with the designated color
 */
void clear_screen(unsigned char color);

/*
 * Draws the current buffer
 */
void draw();