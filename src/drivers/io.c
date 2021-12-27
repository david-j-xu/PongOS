#include "io.h"

/*
 * Read a byte from the specified port
 */
u_8t io_byte_read(u_16t port) {
    u_8t result;
    __asm__ volatile("in %%dx, %%al" : "=a"(result) : "d"(port));
    return result;
}

/*
 * Write a byte to the specified port
 */
void io_byte_write(u_16t port, u_8t data) {
    __asm__ volatile("out %%al, %%dx" : : "a"(data), "d"(port));
}

/*
 * Read a word from the specified port
 */
u_16t io_word_read(u_16t port) {
    u_16t result;
    __asm__ volatile("in %%dx, %%ax" : "=a"(result) : "d"(port));
    return result;
}

/*
 * Write a word to the specified port
 */
void io_word_write(u_16t port, u_8t data) {
    __asm__ volatile("out %%ax, %%dx" : : "a"(data), "d"(port));
}