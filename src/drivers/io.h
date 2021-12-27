#pragma once
#include "utils.h"

/*
 * Read a byte from the specified port
 */
u_8t io_byte_read(unsigned short port);

/*
 * Write a byte to the specified port
 */
void io_byte_write(unsigned short port, unsigned char data);

/*
 * Read a word from the specified port
 */
u_16t io_word_read(unsigned short port);

/*
 * Write a word to the specified port
 */
void io_word_write(unsigned short port, unsigned char data);