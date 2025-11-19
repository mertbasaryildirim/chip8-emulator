#include "display_manager.h"
#include "chip8.h"

DisplayManager g_displayManager;

int DisplayManager_Init(const char *title)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        return 0;

    int windowWidth = CHIP8_WIDTH * CHIP8_PIXEL_SCALE;
    int windowHeight = CHIP8_HEIGHT * CHIP8_PIXEL_SCALE;

    g_displayManager.window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        windowWidth,
        windowHeight,
        SDL_WINDOW_SHOWN);
    if (!g_displayManager.window)
        return 0;

    g_displayManager.renderer =
        SDL_CreateRenderer(g_displayManager.window, -1, SDL_RENDERER_ACCELERATED);
    if (!g_displayManager.renderer)
        return 0;

    g_displayManager.texture =
        SDL_CreateTexture(
            g_displayManager.renderer,
            SDL_PIXELFORMAT_RGBA8888,
            SDL_TEXTUREACCESS_STREAMING,
            CHIP8_WIDTH,
            CHIP8_HEIGHT);
    if (!g_displayManager.texture)
        return 0;

    return 1;
}

void DisplayManager_Destroy()
{
    SDL_DestroyTexture(g_displayManager.texture);
    SDL_DestroyRenderer(g_displayManager.renderer);
    SDL_DestroyWindow(g_displayManager.window);
    SDL_Quit();
}

void DisplayManager_Update()
{
    uint32_t pixels[CHIP8_HEIGHT][CHIP8_WIDTH];

    for (int y = 0; y < CHIP8_HEIGHT; y++)
    {
        for (int x = 0; x < CHIP8_WIDTH; x++)
        {
            pixels[y][x] = chip8_memory.display[y][x]
                               ? 0xFFFFFFFF
                               : 0xFF000000;
        }
    }

    SDL_UpdateTexture(g_displayManager.texture, NULL, pixels, CHIP8_WIDTH * sizeof(uint32_t));
    SDL_RenderClear(g_displayManager.renderer);
    SDL_RenderCopy(g_displayManager.renderer, g_displayManager.texture, NULL, NULL);
    SDL_RenderPresent(g_displayManager.renderer);
}

int DisplayManager_ProcessInput()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
            return 1;

        else if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                return 1;
            case SDLK_x:
                chip8_memory.keypad[0] = 1;
                break;
            case SDLK_1:
                chip8_memory.keypad[1] = 1;
                break;
            case SDLK_2:
                chip8_memory.keypad[2] = 1;
                break;
            case SDLK_3:
                chip8_memory.keypad[3] = 1;
                break;
            case SDLK_q:
                chip8_memory.keypad[4] = 1;
                break;
            case SDLK_w:
                chip8_memory.keypad[5] = 1;
                break;
            case SDLK_e:
                chip8_memory.keypad[6] = 1;
                break;
            case SDLK_a:
                chip8_memory.keypad[7] = 1;
                break;
            case SDLK_s:
                chip8_memory.keypad[8] = 1;
                break;
            case SDLK_d:
                chip8_memory.keypad[9] = 1;
                break;
            case SDLK_z:
                chip8_memory.keypad[0xA] = 1;
                break;
            case SDLK_c:
                chip8_memory.keypad[0xB] = 1;
                break;
            case SDLK_4:
                chip8_memory.keypad[0xC] = 1;
                break;
            case SDLK_r:
                chip8_memory.keypad[0xD] = 1;
                break;
            case SDLK_f:
                chip8_memory.keypad[0xE] = 1;
                break;
            case SDLK_v:
                chip8_memory.keypad[0xF] = 1;
                break;
            }
        }

        else if (event.type == SDL_KEYUP)
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_x:
                chip8_memory.keypad[0] = 0;
                break;
            case SDLK_1:
                chip8_memory.keypad[1] = 0;
                break;
            case SDLK_2:
                chip8_memory.keypad[2] = 0;
                break;
            case SDLK_3:
                chip8_memory.keypad[3] = 0;
                break;
            case SDLK_q:
                chip8_memory.keypad[4] = 0;
                break;
            case SDLK_w:
                chip8_memory.keypad[5] = 0;
                break;
            case SDLK_e:
                chip8_memory.keypad[6] = 0;
                break;
            case SDLK_a:
                chip8_memory.keypad[7] = 0;
                break;
            case SDLK_s:
                chip8_memory.keypad[8] = 0;
                break;
            case SDLK_d:
                chip8_memory.keypad[9] = 0;
                break;
            case SDLK_z:
                chip8_memory.keypad[0xA] = 0;
                break;
            case SDLK_c:
                chip8_memory.keypad[0xB] = 0;
                break;
            case SDLK_4:
                chip8_memory.keypad[0xC] = 0;
                break;
            case SDLK_r:
                chip8_memory.keypad[0xD] = 0;
                break;
            case SDLK_f:
                chip8_memory.keypad[0xE] = 0;
                break;
            case SDLK_v:
                chip8_memory.keypad[0xF] = 0;
                break;
            }
        }
    }

    return 0;
}
