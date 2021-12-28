/*
 * Keyboard driver
 */
#pragma once
#include "idt.h"
#include "io.h"
#include "pic.h"
#include "utils.h"

#define KBD_DATA 0x60
#define KBD_INT 0x21

#define KEY_ESC 0x01
#define KEY_W 0x11
#define KEY_S 0x1F
#define KEY_R 0x13
#define KEY_UP 0x48
#define KEY_DOWN 0x50

#define KEYBOARD_RELEASE 0x80

#define KEY_PRESSED(s) (!(KEYBOARD_RELEASE & s))

typedef struct Keyboard Keyboard;

struct Keyboard {
    u_8t keys[128];
};

void kb_irq_handler();

void kb_init();