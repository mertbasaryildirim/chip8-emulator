/*
 * CHIP-8 Core Interface
 *
 * This header defines the high-level interface for initializing,
 * configuring, and loading programs into the CHIP-8 virtual machine.
 * It exposes the global MEMORY instance, ROM-loading routines, and
 * initialization functions. The emulator's state is entirely encapsulated
 * within the MEMORY structure (defined in memory.h), while this file
 * provides the public API to access and manipulate it.
 */

#ifndef CHIP8_H
#define CHIP8_H

#include <stdint.h>
#include "memory.h"

/*
 * chip8_memory
 *
 * Global instance representing the entire CHIP-8 machine state.
 * This includes RAM, registers, stack, timers, index register,
 * keypad mapping, and the display buffer. The MEMORY struct
 * defined in memory.h
 *
 * All instructions and processing routines interact with this object.
 */
extern MEMORY chip8_memory;

/*
 * chip8_init()
 *
 * Initializes the CHIP-8 virtual machine.
 *
 * This function:
 *   - Seeds the RNG for random-number instructions (Cxkk)
 *   - Loads the built-in font sprites into memory starting at 0x50
 *   - Resets the program counter to 0x200 (standard start address)
 *   - Initializes opcode dispatch tables
 *
 * Must be called before loading and executing any CHIP-8 ROM.
 */
void chip8_init();

/*
 * chip8_generate_random_number()
 *
 * Returns an 8-bit random value (0–255).
 *
 * Used primarily by the Cxkk (RND Vx, byte) instruction. The value is
 * masked by the instruction handler to apply the correct bit-filtering
 * semantics defined by the CHIP-8 specification.
 */
uint8_t chip8_generate_random_number();

/*
 * chip8_load_ROM(filename)
 *
 * Loads a CHIP-8 ROM from disk into memory beginning at address 0x200.
 *
 * The routine:
 *   - Opens the file in binary mode
 *   - Determines file size and ensures it fits in the remaining memory
 *   - Copies the ROM bytes sequentially into RAM starting at START_ADDRESS
 *   - Returns 0 on success, or -1 on any failure (I/O errors, oversized ROM)
 *
 * The program counter is *not* modified here; chip8_init() sets it.
 */
int chip8_load_ROM(const char *filename);

#endif
