#ifndef OPCODE_TABLE_H
#define OPCODE_TABLE_H

#include <stdint.h>

// Global current opcode
extern uint16_t ot_opcode;

// Initialize all dispatch tables
void ot_init(void);

// Execute current opcode using dispatch table
void ot_execute(void);

#endif
