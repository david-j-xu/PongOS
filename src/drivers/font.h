#pragma once
#include "screen.h"
#include "utils.h"

/* draws a character at the specified location */
void draw_char(u_16t x, u_16t y, char c, u_8t color);

/* draws a string at the specified location */
void draw_string(u_16t x, u_16t y, char* s, u_8t color);