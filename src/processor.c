#include "chip8.h"
#include "opcode_table.h"

void processor_cycle(void)
{
    /* Fetch opcode (big-endian) */
    opcode = (chip8_memory.ram[chip8_memory.program_counter] << 8) |
             (chip8_memory.ram[chip8_memory.program_counter + 1]);

    /* Advance program counter */
    chip8_memory.program_counter += 2;

    /* Decode + Execute */
    ot_execute();

    /* Timers */
    if (chip8_memory.delay_timer > 0)
        chip8_memory.delay_timer--;

    if (chip8_memory.sound_timer > 0)
        chip8_memory.sound_timer--;
}
