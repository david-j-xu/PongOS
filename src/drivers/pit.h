/*
 * Timer driver
 */
#pragma once

#include "idt.h"
#include "io.h"
#include "utils.h"

#define PIT_A 0x40
#define PIT_B 0x41
#define PIT_C 0x42
#define PIT_CONTROL 0x43
#define PIT_MASK 0xFF
#define PIT_SET 0x36
#define PIT_FREQ 1193131.666
#define TIMER_INT 0x20

/*
 * Initialize PIT
 */
void timer_init();

/*
 * Get current time
 */
u_64t timer_get();

/*
 * Set the timer frequency
 */
void set_timer_freq(int hz);

/*
 * Set timer handler
 */
void timer_handler();