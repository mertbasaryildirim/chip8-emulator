#include "instructions.h"
#include "chip8.h"
#include "opcode_table.h"

void OP_00E0()
{
    memset(chip8_memory.display, 0, sizeof(chip8_memory.display));
}

void OP_00EE()
{
    --chip8_memory.stack_pointer;
    chip8_memory.program_counter = *(chip8_memory.stack + chip8_memory.stack_pointer);
}

void OP_1nnn()
{
    chip8_memory.program_counter = opcode & 0x0FFFu;
}

void OP_2nnn()
{
    *(chip8_memory.stack + chip8_memory.stack_pointer++) = chip8_memory.program_counter;
    chip8_memory.program_counter = opcode & 0x0FFFu;
}

void OP_3xkk()
{
    uint8_t register_address = (opcode & 0x0F00u) >> 8u;
    uint8_t register_value = *(chip8_memory.registers + register_address);

    if (register_value == (opcode & 0x00FFu))
        chip8_memory.program_counter += 2;
}
