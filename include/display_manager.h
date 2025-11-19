#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include <stdint.h>
#include <SDL2/SDL.h>

#define CHIP8_WIDTH 64
#define CHIP8_HEIGHT 32
#define CHIP8_PIXEL_SCALE 10

typedef struct
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
} DisplayManager;

extern DisplayManager g_displayManager;

int DisplayManager_Init(const char *title);
void DisplayManager_Destroy();
void DisplayManager_Update();
int DisplayManager_ProcessInput();

#endif
