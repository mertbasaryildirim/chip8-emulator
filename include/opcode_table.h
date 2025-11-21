/*
 * OPCODE DISPATCH TABLE SYSTEM
 *
 * This module provides the decoding and dispatch mechanism for CHIP-8 opcodes.
 * CHIP-8 instructions are 16-bit values, composed of several fields that
 * determine the instruction class, register operands, and immediate values.
 *
 * Instead of using large switch–case blocks, this implementation uses
 * multi-level function tables, providing a clean and fast way to map opcodes
 * to their corresponding handler functions.
 *
 * STRUCTURE:
 *   - mainTable[16]     — Dispatches based on the highest nibble (0xF000 >> 12)
 *   - table0[16]        — Handles 0x0*** opcodes differentiated by lowest nibble
 *   - table8[16]        — Handles 0x8xy? opcodes (bitwise/arithmetic instructions)
 *   - tableE[16]        — Handles Ex9E / ExA1 opcodes based on lowest nibble
 *   - tableF[0x100]     — Handles all Fx** opcodes (full low byte indexing)
 *
 * This design cleanly mirrors how CHIP-8 opcodes are structured and avoids
 * deeply nested logic or repeated mask operations.
 */

#ifndef OPCODE_TABLE_H
#define OPCODE_TABLE_H

#include <stdint.h>

/*
 * opcode
 *
 * Holds the 16-bit instruction currently being executed.
 * This global variable is assigned during the fetch phase inside processor_cycle().
 *
 * Access Patterns:
 *   - Instruction handlers read fields directly by masking/shifting
 *   - The dispatcher indexes tables based on its high/low nibbles/bytes
 *
 * Example:
 *   High nibble → (opcode & 0xF000) >> 12
 *   Low byte    → (opcode & 0x00FF)
 */
extern uint16_t opcode;

/*
 * ot_init()
 *
 * Initializes the opcode dispatch system.
 *
 * Responsibilities:
 *   - Clears all dispatch tables and sets unimplemented entries to OP_NULL
 *   - Assigns opcode groups (0, 8, E, F) to appropriate sub-tables
 *   - Populates each table based on the CHIP-8 specification
 *   - Ensures every valid opcode has an associated function pointer
 *
 * Must be called before any CPU cycle occurs; typically invoked during chip8_init().
 */
void ot_init(void);

/*
 * ot_execute()
 *
 * Performs the execution dispatch for the current opcode.
 *
 * Steps:
 *   1. Extract top nibble (0xF000 >> 12)
 *   2. Select handler from mainTable[]
 *   3. If the opcode group requires deeper decoding (e.g., 0x8, 0xF),
 *      the handler function performs an additional lookup into its
 *      corresponding secondary table.
 *   4. Invoke final handler function
 *
 * Execution side effects occur entirely within instruction handler functions.
 */
void ot_execute(void);

#endif
