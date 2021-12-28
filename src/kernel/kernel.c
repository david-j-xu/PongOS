#include "kernel.h"

Keyboard keyboard;

void main() {
    idt_init(IDT);
    pic_init();
    kb_init();
    timer_init();
    sti();
    init_screen();

    clear_screen(COLOR(0, 0, 0));

    for (;;) {
        if (keyboard.keys[KEY_DOWN]) {
            draw_string(50, 50, "DOWN", WHITE);
        }

        if (keyboard.keys[KEY_UP]) {
            draw_string(50, 60, "UP", WHITE);
        }

        draw_hex(10, 10, (u_32t)timer_get(), timer_get() % 256);

        draw();
    }

    halt();
}
