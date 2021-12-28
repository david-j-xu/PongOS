#include "keyboard.h"

extern Keyboard keyboard;

void kb_irq_handler() {
    __asm__ volatile("pusha");
    u_16t scancode = (u_16t)io_byte_read(KBD_DATA);

    /* if key was pressed, set to 1. If released, set to 0 */
    keyboard.keys[scancode] = KEY_PRESSED(scancode);
    end_of_interrupt();
    __asm__ volatile("popa");
    __asm__ volatile("leave");
    __asm__ volatile("iret");
}

void kb_init() {
    install_irq_handler(0x21, FLAGS, IDT, (IRQ_HANDLER)kb_irq_handler);
}