#include <stdint.h>
#include "chip8.h"

void processor_cycle()
{
    // Fetch
    uint16_t opcode = *(chip8_memory.ram + chip8_memory.program_counter) |
                      *(chip8_memory.ram + chip8_memory.program_counter + 1);

    // Update the program counter before execution
    chip8_memory.program_counter += 2;

    // Decode and Execute

    // Update the timers if necessary
    chip8_memory.delay_timer -= (chip8_memory.delay_timer > 0) ? 1 : 0;
    chip8_memory.sound_timer -= (chip8_memory.sound_timer > 0) ? 1 : 0;
}