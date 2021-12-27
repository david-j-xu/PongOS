#include "kernel.h"

void main() {
    init_screen();

    clear_screen(COLOR(0, 0, 0));

    draw_string(50, 50, "Hello World!", WHITE);
    draw_rectangle(10, 100, 20, 50, COLOR(7, 7, 2));
    draw_circle(250, 140, 40, COLOR(7, 3, 3));
    draw();

    halt();
}
