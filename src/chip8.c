#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include "chip8.h"

MEMORY chip8_memory = {0};

static void chip8_load_fonts()
{
    uint8_t fontset[FONTSET_SIZE] =
        {
            0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
            0x20, 0x60, 0x20, 0x20, 0x70, // 1
            0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
            0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
            0x90, 0x90, 0xF0, 0x10, 0x10, // 4
            0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
            0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
            0xF0, 0x10, 0x20, 0x40, 0x40, // 7
            0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
            0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
            0xF0, 0x90, 0xF0, 0x90, 0x90, // A
            0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
            0xF0, 0x80, 0x80, 0x80, 0xF0, // C
            0xE0, 0x90, 0x90, 0x90, 0xE0, // D
            0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
            0xF0, 0x80, 0xF0, 0x80, 0x80  // F
        };

    for (unsigned int i = 0; i < FONTSET_SIZE; ++i)
    {
        chip8_memory.ram[FONTSET_START_ADDRESS + i] = fontset[i];
    }
}

static void chip8_reset_pc()
{
    chip8_memory.program_counter = START_ADDRESS;
}

void chip8_init()
{
    srand(time(NULL));
    chip8_load_fonts();
    chip8_reset_pc();
}

uint8_t chip8_generate_random_number()
{
    return rand() % 256;
}

int chip8_load_ROM(const char *filename)
{
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL)
    {
        perror("Failed to open ROM file");
        return -1;
    }

    // Determine file size
    if (fseek(fp, 0, SEEK_END) != 0)
    {
        perror("fseek (SEEK_END) failed");
        fclose(fp);
        return -1;
    }

    long size = ftell(fp);
    if (size < 0)
    {
        perror("ftell failed");
        fclose(fp);
        return -1;
    }

    // Check if the ROM fits into CHIP-8 memory
    if (size > (4096 - START_ADDRESS))
    {
        fprintf(stderr,
                "ERROR: ROM size (%ld bytes) is too large. "
                "It cannot fit into CHIP-8 memory.\n",
                size);
        fclose(fp);
        return -1;
    }

    rewind(fp);

    // Read ROM into memory
    size_t bytes_read = fread(
        chip8_memory.ram + START_ADDRESS,
        1,
        size,
        fp);

    if (bytes_read != size)
    {
        if (ferror(fp))
            perror("Error while reading ROM file");
        else
            fprintf(stderr, "Unexpected: fread read fewer bytes than expected.\n");

        fclose(fp);
        return -1;
    }

    fclose(fp);
    return 0;
}