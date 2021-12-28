/*
 * Programmable Interrupt Controller Driver
 */
#pragma once
#include "io.h"
#include "utils.h"

#define PIC_1_CMD_PORT 0x20
#define PIC_1_DATA_PORT 0x21
#define PIC_2_CMD_PORT 0xA0
#define PIC_2_DATA_PORT 0xA1

#define END_OF_INTERRUPT 0x20
#define PIC_READ_IRR 0x0A
#define PIC_READ_ISR 0x0B

/* initialize + wait for ICW 4 */
#define ICW1_INIT_ICW4 0x11

#define ICW2_PIC_1_OFFSET 0x20
#define ICW2_PIC_2_OFFSET 0x28

#define ICW3_PIC_IRQ 0x4
#define ICW3_CASCADE 0x2

#define ICW4_8086 0x01

/*
 * Initialize the PIC
 */
void pic_init();

/*
 * Read for which interrupt
 */
u_8t pic_read_irr();

/*
 * Read for current interrupt
 */
u_8t pic_read_isr();
