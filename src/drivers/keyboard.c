#include "keyboard.h"

extern Keyboard keyboard;

void kb_irq_handler() {
    __asm__ volatile("pusha");
    u_16t scancode = (u_16t)io_byte_read(KBD_DATA);

    /* set highbit */
    int key_code = scancode & 0x7F;

    /* if key was pressed, set to 1. If released, set to 0 */
    keyboard.keys[key_code] = KEY_PRESSED(scancode);

    end_of_interrupt();
    __asm__ volatile("popa");
    __asm__ volatile("leave");
    __asm__ volatile("iret");
}

void kb_init() {
    install_irq_handler(KBD_INT, FLAGS, IDT, (IRQ_HANDLER)kb_irq_handler);
}

u_8t check_key(u_8t key) { return keyboard.keys[key]; }

u_8t check_and_reset_key(u_8t key) {
    u_8t state = keyboard.keys[key];
    keyboard.keys[key] = 0;
    return state;
}