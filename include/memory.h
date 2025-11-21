/*
 * MEMORY Structure and CHIP-8 Core Memory Layout
 *
 * This structure models the entire state of the CHIP-8 virtual machine.
 * It encapsulates RAM, registers, timers, stack, the display buffer, and
 * keypad state. Each component corresponds directly to elements of the
 * original 1970s CHIP-8 specification.
 *
 * Memory Map (4096 bytes total):
 * ┌────────────┬────────────────────────────────────────────────────────┐
 * │ 0x000–0x1FF│ Reserved (interpreter area in original systems)        │
 * │ 0x050–0x09F│ Built-in 4×5 font sprites (loaded during startup)      │
 * │ 0x200–0xFFF│ Program space — ROM is loaded starting at 0x200        │
 * └────────────┴────────────────────────────────────────────────────────┘
 *
 * This header only defines the structure and constants; initialization logic
 * is implemented inside chip8.c.
 */

#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>
#include <stdbool.h>

/*
 * FONTSET_SIZE
 *
 * Number of bytes in the built-in CHIP-8 hexadecimal font set.
 * Each digit (0–F) uses 5 bytes, so the total is 16 × 5 = 80 bytes.
 */
#define FONTSET_SIZE 80

/*
 * FONTSET_START_ADDRESS
 *
 * Memory address where the built-in font sprites are loaded.
 * According to the traditional CHIP-8 implementation, fonts are stored
 * beginning at 0x50, leaving room for interpreter space before it.
 */
#define FONTSET_START_ADDRESS 0x50

/*
 * START_ADDRESS
 *
 * Programs are loaded beginning at memory address 0x200.
 * Classic CHIP-8 interpreters reserved the first 512 bytes for their
 * own implementation, so user programs always begin at 0x200.
 */
#define START_ADDRESS 0x200

/*
 * MEMORY
 *
 * Represents the full CHIP-8 machine state.
 *
 * registers[16]
 *   - General-purpose 8-bit registers V0–VF.
 *   - VF is used as a flag register for arithmetic and collision detection.
 *
 * ram[4096]
 *   - The full 4 KB memory space. Used for instructions, data, and sprites.
 *
 * index
 *   - The 16-bit index register I used for addressing memory.
 *
 * program_counter
 *   - Points to the currently executing instruction.
 *
 * stack[16] / stack_pointer
 *   - Used during subroutine calls. Stores return addresses.
 *   - stack_pointer points to the next empty slot.
 *
 * delay_timer / sound_timer
 *   - Timers count down at 60 Hz when non-zero.
 *   - sound_timer triggers a beep while greater than zero.
 *
 * keypad[16]
 *   - Logical state of the 16 hexadecimal keypad keys.
 *   - Keys map to: 0–F.
 *
 * display[32][64]
 *   - 64×32 monochrome display buffer.
 *   - Each pixel is represented as a 32-bit value (ARGB/RGBA depending on renderer).
 */
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
