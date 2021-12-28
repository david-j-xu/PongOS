/*
 * Defines and initializes the interrupt descriptor table and handlers
 */

#pragma once
#include "io.h"
#include "pic.h"
#include "utils.h"

#define IDT 0x08
#define MAX_INTERRUPTS 256
#define INTERRUPTS_IVT 32
#define FLAGS 0x8E
#define PACKED __attribute__((packed))

/*function signature for an interrupt handler */
typedef void (*IRQ_HANDLER)(void);

/* Interrupt descriptor */
struct idt_entry {
    u_16t base_low;   // offset bits 0 to 15
    u_16t selector;   // a code seg selector in GDT or LDT
    u_8t reserved;    // unused, set to 0
    u_8t flags;       // type and attributes
    u_16t base_high;  // offset bits 16 to 31
} PACKED;

/* Interrupt desciptor table pointer */
struct idt_p {
    u_16t limit;
    u_32t base;
} PACKED;

typedef struct idt_entry idt_entry;
typedef struct idt_p idt_p;

void idt_install();
/*
 * Initializes the interrupt descriptor table
 */
int idt_init(u_16t code_selector);

/*
 * Installs an interrupt handle
 */
void install_irq_handler(u_32t i, u_8t flags, u_16t selector, IRQ_HANDLER irq);

/*
 * Default interrupt handler
 */
void default_handler();

/*
 * Denotes the end of an interrupt
 */
void end_of_interrupt();