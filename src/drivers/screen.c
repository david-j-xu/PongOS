#include "screen.h"

void clear_screen(u_8t color) { memset(&VGA_BUFFER, color, SCREEN_SIZE); }

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
}