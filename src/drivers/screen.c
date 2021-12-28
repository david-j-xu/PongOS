#include "screen.h"

u_8t padding[SCREEN_SIZE];
u_8t buffers[2][SCREEN_SIZE];
u_8t curr_buffer = 1;

void clear_screen(u_8t color) { memset(VGA_BUFFER, color, SCREEN_SIZE); }

void init_screen() {
    /* allow all colors through */
    io_byte_write(VGA_PALETTE_MASK, 0xFF);
    /* allow writing */
    io_byte_write(VGA_CONTROL_WRITE, 0);
    /* populate first 255 colors */
    for (u_8t i = 0; i < 255; i++) {
        io_byte_write(VGA_CONTROL_DATA, ((i >> 5) & 0x7) * 8);
        io_byte_write(VGA_CONTROL_DATA, ((i >> 2) & 0x7) * 8);
        io_byte_write(VGA_CONTROL_DATA, ((i >> 0) & 0x3) * 8);
    }

    /* set final color to white */
    io_byte_write(VGA_CONTROL_DATA, 0x3F);
    io_byte_write(VGA_CONTROL_DATA, 0x3F);
    io_byte_write(VGA_CONTROL_DATA, 0x3F);

    /* clear buffers */

    for (u_8t i = 0; i < 2; i++) memset(buffers[i], NULL, SCREEN_SIZE);
}

static u_16t get_screen_pos(u_16t x, u_16t y) { return 320 * y + x; }

static u_8t in_bounds(u_16t x, u_16t y) {
    return !!(x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT);
}

void set_pixel(u_16t x, u_16t y, u_8t color) {
    if (in_bounds(x, y)) buffers[curr_buffer][get_screen_pos(x, y)] = color;
}

void draw_rectangle(u_16t x, u_16t y, u_16t w, u_16t h, u_8t color) {
    for (int i = x; i < x + w; i++) {
        for (int j = y; j < y + h; j++) {
            set_pixel(i, j, color);
        }
    }
}

void draw_circle(u_16t x, u_16t y, u_16t r, u_8t color) {
    for (int i = x - r; i <= x + r; i++) {
        for (int j = y - r; j <= y + r; j++) {
            if (dist_decision(i, j, x, y, r)) set_pixel(i, j, color);
        }
    }
}

void draw() {
    memcpy(VGA_BUFFER, buffers[curr_buffer], SCREEN_SIZE);
    memset(buffers[curr_buffer], 0, SCREEN_SIZE);
    /* swap buffers */
    curr_buffer = 1 - curr_buffer;
}