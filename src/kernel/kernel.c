#include "kernel.h"

Keyboard keyboard;

void main() {
    idt_init(IDT);
    pic_init();
    kb_init();
    timer_init();
    init_screen();
    clear_screen(COLOR(0, 0, 0));
    sti();

    Pong game;
    create_game(&game);
    event_loop(&game);

    halt();
}
