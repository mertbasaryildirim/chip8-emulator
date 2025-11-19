#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>
#include <stdbool.h>

#define FONTSET_SIZE 80
#define FONTSET_START_ADDRESS 0x50
#define START_ADDRESS 0x200

typedef struct
{
    uint8_t registers[16];
    uint8_t ram[4096];
    uint16_t index;
    uint16_t program_counter;
    uint16_t stack[16];
    uint8_t stack_pointer;
    uint8_t delay_timer;
    uint8_t sound_timer;
    uint8_t keypad[16];
    uint32_t display[32][64];
} MEMORY;

#endif