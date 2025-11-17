#include "instructions.h"
#include "chip8.h"

void OP_00E0()
{
    memset(chip8_memory.display, 0, sizeof(chip8_memory.display));
}

void OP_00EE()
{
    --chip8_memory.stack_pointer;
    chip8_memory.program_counter = *(chip8_memory.stack + chip8_memory.stack_pointer);
}