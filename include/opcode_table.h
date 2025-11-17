#ifndef OPCODE_TABLE_H
#define OPCODE_TABLE_H

#include <stdint.h>

// Global current opcode
extern uint16_t chip8_opcode;

// Initialize all dispatch tables
void chip8_init_opcode_table(void);

// Execute current opcode using dispatch table
void chip8_execute_opcode(void);

#endif
