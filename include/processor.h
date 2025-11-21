/*
 * CHIP-8 Processor Interface
 *
 * This header declares the CPU execution entry point for the CHIP-8 emulator.
 * It exposes a single function, processor_cycle(), responsible for performing
 * one full fetch–decode–execute step and updating system timers. All CPU state
 * (registers, memory, stack, timers) resides in chip8_memory.
 */

#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "chip8.h"

/*
 * processor_cycle()
 *
 * Executes exactly one CPU cycle:
 *   - Fetches the next opcode from memory
 *   - Advances the program counter
 *   - Dispatches and executes the instruction
 *   - Updates delay and sound timers
 *
 * This function must be called repeatedly from the main emulation loop.
 */
void processor_cycle();

#endif
