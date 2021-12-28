#include "kernel.h"

Keyboard keyboard;

void main() {
    // idt_init(IDT);
    pic_init();
    // kb_init();
    sti();
    init_screen();
    // cli();

    clear_screen(COLOR(0, 0, 0));

    for (;;) {
        int i = 0;
        draw_string(50, 50, "Hello World!", WHITE);
        draw_char(20, 20, 'A' + i, WHITE);
        if (keyboard.keys[KEY_DOWN]) {
            i++;
            draw_string(70, 50, "DOWN", WHITE);
        }
        if (keyboard.keys[KEY_UP]) {
            i++;
            draw_string(70, 50, "UP", WHITE);
        }

        draw();
    }

    halt();
}
