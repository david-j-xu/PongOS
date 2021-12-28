#include "pit.h"

static u_64t ticks = 0;

void timer_init() {
    ticks = 0;
    // install_irq_handler(TIMER_INT, FLAGS, IDT, (IRQ_HANDLER)default_handler);

    install_irq_handler(TIMER_INT, FLAGS, IDT, (IRQ_HANDLER)timer_handler);
}

u_64t timer_get() { return ticks; }

void timer_handler() {
    __asm__ volatile("pusha");

    ticks++;
    end_of_interrupt();
    __asm__ volatile("popa");
    __asm__ volatile("leave");
    __asm__ volatile("iret");
}

void set_timer_freq(int hz) {
    io_byte_write(PIT_CONTROL, PIT_SET);

    u_16t d = (u_16t)(PIT_FREQ / hz);
    io_byte_write(PIT_A, d & PIT_MASK);
    io_byte_write(PIT_A, (d >> 8) & PIT_MASK);
}