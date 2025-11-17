#include "instructions.h"
#include "chip8.h"

void OP_00E0()
{
    memset(chip8_memory.display, 0, sizeof(chip8_memory.display));
}