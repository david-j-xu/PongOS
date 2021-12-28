#include "pic.h"

void pic_init() {
    u_8t pic1_mask = 0xFC;  // block all interrupts besides timer and keyboard
    u_8t pic2_mask = 0xFF;  // block all interrupts

    /* initialize PICs */
    io_byte_write(PIC_1_CMD_PORT, ICW1_INIT_ICW4);
    io_byte_write(PIC_2_CMD_PORT, ICW1_INIT_ICW4);
    io_byte_write(PIC_1_DATA_PORT, ICW2_PIC_1_OFFSET);
    io_byte_write(PIC_2_DATA_PORT, ICW2_PIC_2_OFFSET);
    io_byte_write(PIC_1_DATA_PORT, ICW3_PIC_IRQ);
    io_byte_write(PIC_2_DATA_PORT, ICW3_CASCADE);
    io_byte_write(PIC_1_DATA_PORT, ICW4_8086);
    io_byte_write(PIC_2_DATA_PORT, ICW4_8086);

    /* load all masks */
    io_byte_write(PIC_1_DATA_PORT, pic1_mask);
    io_byte_write(PIC_2_DATA_PORT, pic2_mask);
}

u_8t pic_read_irr() {
    io_byte_write(PIC_1_CMD_PORT, PIC_READ_IRR);
    return io_byte_read(PIC_1_CMD_PORT);
}

u_8t pic_read_isr() {
    io_byte_write(PIC_1_CMD_PORT, PIC_READ_ISR);
    return io_byte_read(PIC_1_CMD_PORT);
}