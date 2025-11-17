#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>

typedef struct
{
    uint8_t registers[16];
    uint8_t memory[4096];
    uint16_t index;
    uint16_t program_counter;
    uint16_t stack[16];
    uint8_t stack_pointer;
    uint8_t delay_timer;
    uint8_t sounds_timer;
    uint8_t keypad[16];
    uint32_t video[64][32];
    uint16_t opcode;
} MEMORY;

MEMORY chip8_memory = {0};

#endif