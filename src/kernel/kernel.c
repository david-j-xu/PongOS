#include "kernel.h"

void main() {
    init_screen();
    char* video_memory = (char*)0xA0000;
    for (u_16t i = 0; i < SCREEN_SIZE; i++) {
        video_memory[i] = COLOR(7, 7, 3);
    }
}

void cli() { __asm__ volatile("cli"); }
void sti() { __asm__ volatile("sti"); }