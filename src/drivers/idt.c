#include "idt.h"

static idt_entry idt[MAX_INTERRUPTS];
static idt_p idt_pointer;

void idt_install() { __asm__ volatile("lidt %0" ::"m"(idt_pointer)); }

int idt_init(u_16t code_selector) {
    idt_pointer.limit = sizeof(idt_entry) * MAX_INTERRUPTS - 1;
    idt_pointer.base = (u_32t)&idt;

    /* install CPU interrupt handlers */
    for (int i = 0; i < INTERRUPTS_IVT; ++i)
        install_irq_handler(i, FLAGS, code_selector, &default_handler);

    /* install idt */
    idt_install();

    return 0;
}

void install_irq_handler(u_32t i, u_8t flags, u_16t selector,
                         IRQ_HANDLER handler) {
    /* inserts an interrupt handler in the idt */
    if (i > MAX_INTERRUPTS) return;
    if (!handler) return;

    cli();
    u_32t handler_address = (u_32t)handler;

    /* set handler in IDT */
    idt[i].base_low = (u_16t)(handler_address & 0xffff);
    idt[i].base_high = (u_16t)((handler_address >> 16) & 0xffff);
    idt[i].reserved = 0;
    idt[i].flags = (u_8t)flags;
    idt[i].selector = selector;
    sti();

    return;
}

void default_handler() {
    /* do nothing */
    __asm__("pusha");
    end_of_interrupt();
    __asm__("popa");
    __asm__("leave");
    __asm__("iret");
}

void end_of_interrupt() {
    /* send to programmable interrupt controllers */
    io_byte_write(PIC_1_CMD_PORT, END_OF_INTERRUPT);
    io_byte_write(PIC_2_CMD_PORT, END_OF_INTERRUPT);
}