#include "instructions.h"
#include "chip8.h"
#include "opcode_table.h"

void OP_00E0()
{
    memset(chip8_memory.display, 0, sizeof(chip8_memory.display));
}

void OP_00EE()
{
    chip8_memory.program_counter = chip8_memory.stack[--chip8_memory.stack_pointer];
}

void OP_1nnn()
{
    chip8_memory.program_counter = opcode & 0x0FFFu;
}

void OP_2nnn()
{
    chip8_memory.stack[chip8_memory.stack_pointer++] = chip8_memory.program_counter;
    chip8_memory.program_counter = opcode & 0x0FFFu;
}

void OP_3xkk()
{
    uint8_t register_address = (opcode & 0x0F00u) >> 8u;
    uint8_t register_value = chip8_memory.registers[register_address];

    if (register_value == (opcode & 0x00FFu))
        chip8_memory.program_counter += 2;
}

void OP_4xkk()
{
    uint8_t register_address = (opcode & 0x0F00u) >> 8u;
    uint8_t register_value = chip8_memory.registers[register_address];

    if (register_value != (opcode & 0x00FFu))
        chip8_memory.program_counter += 2;
}

void OP_5xy0()
{
    uint8_t register_address_x = (opcode & 0x0F00u) >> 8u;
    uint8_t register_value_x = chip8_memory.registers[register_address_x];

    uint8_t register_address_y = (opcode & 0x00F0u) >> 4u;
    uint8_t register_value_y = chip8_memory.registers[register_address_y];

    if (register_value_x == register_value_y)
        chip8_memory.program_counter += 2;
}

void OP_6xkk()
{
    uint8_t register_address = (opcode & 0x0F00u) >> 8u;
    uint8_t value = opcode & 0x00FFu;

    chip8_memory.registers[register_address] = value;
}

void OP_7xkk()
{
    uint8_t register_address = (opcode & 0x0F00u) >> 8u;
    uint8_t value = opcode & 0x00FFu;

    chip8_memory.registers[register_address] += value;
}

void OP_8xy0()
{
    uint8_t register_address_x = (opcode & 0x0F00u) >> 8u;
    uint8_t register_address_y = (opcode & 0x00F0u) >> 4u;

    chip8_memory.registers[register_address_x] = chip8_memory.registers[register_address_y];
}

void OP_8xy1()
{
    uint8_t register_address_x = (opcode & 0x0F00u) >> 8u;
    uint8_t register_address_y = (opcode & 0x00F0u) >> 4u;

    chip8_memory.registers[register_address_x] |= chip8_memory.registers[register_address_y];
}

void OP_8xy2()
{
    uint8_t register_address_x = (opcode & 0x0F00u) >> 8u;
    uint8_t register_address_y = (opcode & 0x00F0u) >> 4u;

    chip8_memory.registers[register_address_x] &= chip8_memory.registers[register_address_y];
}

void OP_8xy3()
{
    uint8_t register_address_x = (opcode & 0x0F00u) >> 8u;
    uint8_t register_address_y = (opcode & 0x00F0u) >> 4u;

    chip8_memory.registers[register_address_x] ^= chip8_memory.registers[register_address_y];
}

void OP_8xy4()
{
    uint8_t register_address_x = (opcode & 0x0F00u) >> 8u;
    uint8_t register_address_y = (opcode & 0x00F0u) >> 4u;
    uint16_t sum = chip8_memory.registers[register_address_x] + chip8_memory.registers[register_address_y];

    chip8_memory.registers[0xF] = (sum > 0xFFu) ? 1 : 0;
    chip8_memory.registers[register_address_x] = (uint8_t)sum;
}

void OP_8xy5()
{
    uint8_t register_address_x = (opcode & 0x0F00u) >> 8u;
    uint8_t register_address_y = (opcode & 0x00F0u) >> 4u;

    chip8_memory.registers[0xF] =
        (chip8_memory.registers[register_address_x] > chip8_memory.registers[register_address_y]) ? 1 : 0;
    chip8_memory.registers[register_address_x] -= chip8_memory.registers[register_address_y];
}

void OP_8xy6()
{
    uint8_t register_address = (opcode & 0x0F00u) >> 8u;

    chip8_memory.registers[0xF] = chip8_memory.registers[register_address] & 0x0001u;
    chip8_memory.registers[register_address] >>= 1;
}

void OP_8xy7()
{
    uint8_t register_address_x = (opcode & 0x0F00u) >> 8u;
    uint8_t register_address_y = (opcode & 0x00F0u) >> 4u;

    chip8_memory.registers[0xF] =
        (chip8_memory.registers[register_address_y] > chip8_memory.registers[register_address_x]) ? 1 : 0;
    chip8_memory.registers[register_address_x] =
        chip8_memory.registers[register_address_y] - chip8_memory.registers[register_address_x];
}