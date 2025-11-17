#ifndef CHIP8_H
#define CHIP8_H

#include <stdint.h>
#include "memory.h"

extern MEMORY chip8_memory;

void chip8_init();

uint8_t chip8_generate_random_number();

#endif