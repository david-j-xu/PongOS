#include "kernel.h"

Keyboard keyboard;

void main() {
    idt_init(IDT);
    pic_init();
    kb_init();
    timer_init();
    init_screen();
    sti();

    clear_screen(COLOR(0, 0, 0));

    for (;;) {
        if (keyboard.keys[KEY_DOWN]) draw_string(50, 60, "DOWN", WHITE);
        if (keyboard.keys[KEY_UP]) draw_string(50, 50, "UP", WHITE);
        if (keyboard.keys[KEY_W]) draw_string(30, 50, "W", WHITE);
        if (keyboard.keys[KEY_S]) draw_string(30, 60, "S", WHITE);
        if (keyboard.keys[KEY_ESC]) draw_string(60, 60, "ESC", WHITE);
        if (keyboard.keys[KEY_R]) draw_string(60, 50, "R", WHITE);

        draw_hex(10, 10, (u_32t)timer_get(), timer_get() % 256);

        draw();
    }

    halt();
}
