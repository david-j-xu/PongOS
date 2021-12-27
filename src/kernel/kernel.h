#pragma once

#include "../drivers/io.h"
#include "../drivers/screen.h"
#include "../drivers/utils.h"

/*
 * Pause hardware interrupts
 */
void cli();

/*
 * Resume hardware interrupts
 */
void sti();

/*
 *  Main
 */
void main();