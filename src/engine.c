#include "engine.h"

SDL_Window      *g_window;
SDL_Renderer    *g_renderer;
SDL_Texture     *g_texture;
struct stage    *g_current_stage;

void engine_load(void)
{ 
    /* Load libraries */
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_EVENTS);
    
    /* Create window and renderer */
    SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP, &g_window, &g_renderer);
    SDL_GetCurrentDisplayMode(0, &g_display);

    if (!g_window) {
        FATAL("Could not create window and renderer");
    }
    
    /* Load tileset */
    SDL_Surface *tileset = IMG_Load("tileset.png");
    if (!tileset) {
        FATAL("Unable to load tileset");
    }

    g_texture = SDL_CreateTextureFromSurface(g_renderer, tileset);
    if (!g_texture) {
        FATAL("Unable to create texture from tileset");
    }
    
    SDL_FreeSurface(tileset);
}

void engine_reschedule(void)
{
    if (!g_scheduled) {
        g_scheduled = true;
        SDL_Event event = {
            .type = SDL_USEREVENT
        };
        SDL_PushEvent(&event);
    }
}

void engine_stage(struct stage *stage)
{
    if (g_current_stage) {
        stage_unload(g_current_stage);
        free(g_current_stage);
    }

    g_current_stage = stage;
    stage_load(g_current_stage);
}

void engine_run(void)
{
    /* Main loop */
    SDL_Event event;
    while (1) {
        if (!SDL_WaitEvent(&event)) {
            FATAL("Could not wait for event");
        }

        switch (event.type) {
            case SDL_WINDOWEVENT:
                engine_reschedule();
                break;
            case SDL_USEREVENT:
                /*
                 * Allow queuing more render events, even before we're done.
                 * This take care of every corner cases that might arise from this technique.
                 */
                g_scheduled = false;
                SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
                SDL_RenderClear(g_renderer);
                stage_update(g_current_stage);
                stage_render(g_current_stage, g_renderer);
                SDL_RenderPresent(g_renderer);
                break;
            default:
                stage_handle_event(g_current_stage, &event);
                break;
        }
    }
}

void engine_unload(void)
{
    if (g_current_stage) {
        stage_unload(g_current_stage);
        free(g_current_stage);
    }

    //SDL_FreeTexture(g_texture);
    SDL_DestroyRenderer(g_renderer);
    SDL_DestroyWindow(g_window);
    SDL_Quit();
}
