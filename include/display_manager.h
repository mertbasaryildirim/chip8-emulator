/*
 * DISPLAY SUBSYSTEM — INTERFACE DESCRIPTION
 *
 * This module defines the structures and functions required to visualize
 * the CHIP-8 video buffer using SDL2. The CHIP-8 display consists of a
 * 64×32 monochrome framebuffer, where each pixel is binary (on/off).
 *
 * Since modern rendering systems operate on RGBA pixel buffers, the
 * DisplayManager provides a translation layer that:
 *
 *   - Creates and manages an SDL window and render context
 *   - Converts the CHIP-8 framebuffer into a texture-compatible format
 *   - Presents this texture to the screen each frame
 *   - Captures keyboard input and maps it to the CHIP-8 keypad semantics
 *
 * The DisplayManager is stateless with respect to the CHIP-8 CPU; it merely
 * reads display/keypad data from the global chip8_memory structure.
 */

#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include <stdint.h>
#include <SDL2/SDL.h>

/*
 * CHIP8_WIDTH / CHIP8_HEIGHT
 *
 * Native logical dimensions of the CHIP-8 framebuffer.
 * All rendering is performed at these base dimensions before being
 * scaled to the window.
 */
#define CHIP8_WIDTH 64
#define CHIP8_HEIGHT 32

/*
 * CHIP8_PIXEL_SCALE
 *
 * The integer scale factor applied to each CHIP-8 pixel when producing
 * the window output. A scale of 10 yields a 640×320 final render area.
 */
#define CHIP8_PIXEL_SCALE 10

/*
 * DisplayManager
 *
 * Holds SDL resources required for rendering the CHIP-8 framebuffer:
 *
 *   window   — The top-level SDL window used for display output.
 *   renderer — SDL renderer responsible for clearing, drawing, and presenting.
 *   texture  — Streaming texture updated each frame with the current
 *               CHIP-8 pixel buffer. The texture is always created at
 *               64×32 resolution, matching the CHIP-8 display.
 *
 * All fields are owned and freed by DisplayManager_* routines.
 */
typedef struct
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
} DisplayManager;

/*
 * g_displayManager
 *
 * Global instance providing centralized access to the display system.
 * The emulator uses a single display context for its lifetime.
 */
extern DisplayManager g_displayManager;

/*
 * DisplayManager_Init(title)
 *
 * Initializes the SDL video subsystem and allocates all rendering objects.
 *
 * Responsibilities:
 *   - Initializes SDL2 (video module)
 *   - Creates a window sized to CHIP-8 resolution × scale factor
 *   - Creates a renderer capable of accelerated texture operations
 *   - Creates a streaming texture matching the logical framebuffer size
 *
 * Return Value:
 *   1 — Initialization successful
 *   0 — Error occurred (SDL failure, resource allocation error)
 */
int DisplayManager_Init(const char *title);

/*
 * DisplayManager_Destroy()
 *
 * Releases all SDL resources owned by DisplayManager:
 *   - Destroys texture, renderer, and window
 *   - Shuts down SDL video subsystem
 *
 * Must be called once on emulator shutdown.
 */
void DisplayManager_Destroy();

/*
 * DisplayManager_Update()
 *
 * Uploads the CHIP-8 framebuffer into the SDL texture, then triggers the
 * rendering pipeline:
 *
 *   - Update texture with converted pixel data
 *   - Clear renderer target
 *   - Copy texture onto render target
 *   - Present the rendered frame to the screen
 *
 * This routine must be executed once per emulation cycle to synchronize
 * visual output with CPU execution.
 */
void DisplayManager_Update();

/*
 * DisplayManager_ProcessInput()
 *
 * Polls and processes SDL input events relevant to the CHIP-8 environment.
 *
 * Event Types:
 *   - SDL_QUIT     → Signals emulator termination
 *   - KEYDOWN/UP   → Maps host keyboard keys to CHIP-8 keypad indices
 *
 * Return Value:
 *   1 — Quit requested
 *   0 — Continue running
 *
 * Key Mapping:
 *   CHIP-8 expects a hexadecimal keypad (0–F). SDL keyboard keys are mapped
 *   to these indices based on widely used emulator conventions.
 */
int DisplayManager_ProcessInput();

#endif
