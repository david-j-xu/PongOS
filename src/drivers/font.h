/*
 * Defines fonts and helper functions to draw to screen
 */

#pragma once
#include "screen.h"
#include "utils.h"

/* draws a character at the specified location */
void draw_char(u_16t x, u_16t y, char c, u_8t color);

/* draws a string at the specified location */
void draw_string(u_16t x, u_16t y, char* s, u_8t color);

/* draws a BIG character at the specified location */
void draw_big_char(u_16t x, u_16t y, char c, u_8t color, u_8t scale);

/* draws a BIG character at the specified location in rainbow */
void draw_big_char_r(u_16t x, u_16t y, char c, u_8t scale);

/* draws a BIG string at the specified location */
void draw_big_string(u_16t x, u_16t y, char* s, u_8t color, u_8t scale);

/* draws a BIG string at the specified location in rainbow */
void draw_big_string_r(u_16t x, u_16t y, char* s, u_8t scale);

/* draws a centered BIG string at the specified height */
void draw_big_string_c(u_16t y, char* s, u_8t color, u_8t scale);

/* draws a centered BIG string at the specified height in RAINBOW */
void draw_big_string_cr(u_16t y, char* s, u_8t scale);

/* draws a hexadecimal integer at the specified location */
void draw_hex(u_16t x, u_16t y, u_32t s, u_8t color);

/* draws a decimal integer at the specified location */
void draw_dec(u_16t x, u_16t y, u_8t s, u_8t color);

/* draws a scaled decimal integer at the specified location */
void draw_big_dec(u_16t x, u_16t y, u_8t s, u_8t color, u_8t scale);

/* draws a scaled decimal integer at the specified location in rainbow */
void draw_big_dec_r(u_16t x, u_16t y, u_8t s, u_8t scale);
