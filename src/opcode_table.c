#include "opcode_table.h"
#include "instructions.h"
#include <stdio.h>
#include <stdint.h>

uint16_t chip8_opcode = 0;

typedef void (*OpcodeFunc)(void);

static OpcodeFunc mainTable[0x10];
static OpcodeFunc table0[0x10];
static OpcodeFunc table8[0x10];
static OpcodeFunc tableE[0x10];
static OpcodeFunc tableF[0x66];

static void Table0(void);
static void Table8(void);
static void TableE(void);
static void TableF(void);
static void OP_NULL(void);

void chip8_init_opcode_table(void)
{
    /* Initialize primary dispatch table */
    for (int i = 0; i < 0x10; ++i)
    {
        mainTable[i] = OP_NULL;
    }

    /* Top-level opcode dispatch (high nibble) */
    mainTable[0x0] = Table0;
    mainTable[0x1] = OP_1nnn;
    mainTable[0x2] = OP_2nnn;
    mainTable[0x3] = OP_3xkk;
    mainTable[0x4] = OP_4xkk;
    mainTable[0x5] = OP_5xy0;
    mainTable[0x6] = OP_6xkk;
    mainTable[0x7] = OP_7xkk;
    mainTable[0x8] = Table8;
    mainTable[0x9] = OP_9xy0;
    mainTable[0xA] = OP_Annn;
    mainTable[0xB] = OP_Bnnn;
    mainTable[0xC] = OP_Cxkk;
    mainTable[0xD] = OP_Dxyn;
    mainTable[0xE] = TableE;
    mainTable[0xF] = TableF;

    /* Initialize secondary tables */
    for (int i = 0; i <= 0xE; ++i)
    {
        table0[i] = OP_NULL;
        table8[i] = OP_NULL;
        tableE[i] = OP_NULL;
    }

    /* 0x0*** opcodes (low nibble) */
    table0[0x0] = OP_00E0;
    table0[0xE] = OP_00EE;

    /* 0x8*** opcodes (low nibble) */
    table8[0x0] = OP_8xy0;
    table8[0x1] = OP_8xy1;
    table8[0x2] = OP_8xy2;
    table8[0x3] = OP_8xy3;
    table8[0x4] = OP_8xy4;
    table8[0x5] = OP_8xy5;
    table8[0x6] = OP_8xy6;
    table8[0x7] = OP_8xy7;
    table8[0xE] = OP_8xyE;

    /* 0xE*** opcodes (low nibble) */
    tableE[0x1] = OP_ExA1;
    tableE[0xE] = OP_Ex9E;

    /* 0xF*** opcodes (low byte) */
    for (int i = 0; i <= 0x65; ++i)
    {
        tableF[i] = OP_NULL;
    }

    tableF[0x07] = OP_Fx07;
    tableF[0x0A] = OP_Fx0A;
    tableF[0x15] = OP_Fx15;
    tableF[0x18] = OP_Fx18;
    tableF[0x1E] = OP_Fx1E;
    tableF[0x29] = OP_Fx29;
    tableF[0x33] = OP_Fx33;
    tableF[0x55] = OP_Fx55;
    tableF[0x65] = OP_Fx65;
}

void chip8_execute_opcode(void)
{
    /* Dispatch by high nibble */
    uint8_t index = (uint8_t)((chip8_opcode & 0xF000u) >> 12);
    OpcodeFunc func = mainTable[index];
    func();
}

static void Table0(void)
{
    uint8_t index = (uint8_t)(chip8_opcode & 0x000Fu);
    OpcodeFunc func = table0[index];
    func();
}

static void Table8(void)
{
    uint8_t index = (uint8_t)(chip8_opcode & 0x000Fu);
    OpcodeFunc func = table8[index];
    func();
}

static void TableE(void)
{
    uint8_t index = (uint8_t)(chip8_opcode & 0x000Fu);
    OpcodeFunc func = tableE[index];
    func();
}

static void TableF(void)
{
    uint8_t index = (uint8_t)(chip8_opcode & 0x00FFu);
    OpcodeFunc func = tableF[index];
    func();
}

static void OP_NULL(void)
{
    /* Unhandled opcode */
    fprintf(stderr, "Unhandled opcode: 0x%04X\n", chip8_opcode);
}
