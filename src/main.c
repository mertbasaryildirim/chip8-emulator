#include <stdio.h>
#include <SDL2/SDL.h>

#include "chip8.h"
#include "processor.h"
#include "display_manager.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s <ROM file>\n", argv[0]);
        return 1;
    }

    chip8_init();

    if (!DisplayManager_Init("CHIP-8 Emulator"))
    {
        printf("Failed to initialize display!\n");
        return 1;
    }

    if (chip8_load_ROM(argv[1]) == 1)
    {
        printf("Failed to load ROM!\n");
        return 1;
    }

    int quit = 0;

    while (!quit)
    {
        quit = DisplayManager_ProcessInput();

        processor_cycle();

        DisplayManager_Update();

        SDL_Delay(2);
    }

    DisplayManager_Destroy();
    return 0;
}
