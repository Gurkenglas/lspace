#include "main.h"

int main(int argc, const char **argv)
{
    struct stage *current_stage;

    /* Load libraries */
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO);

    /* Create window and renderer */
    SDL_Window      *window;
    SDL_Renderer    *renderer;
    SDL_DisplayMode  mode;

    SDL_GetCurrentDisplayMode(0, &mode);
    SDL_CreateWindowAndRenderer(mode.w, mode.h, SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_OPENGL, &window, &renderer);

    if (!window) {
        fprintf(stderr, "Could not create window: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    /* Change stage to game */
    current_stage = malloc(sizeof (struct stage_game));
    stage_game_init((struct stage_game *)current_stage);
    
    /* Main loop */
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

    stage_update(current_stage);
    SDL_RenderClear(renderer);
    stage_render(current_stage);
    SDL_RenderPresent(renderer);

    SDL_Delay(3000);

    /* Cleanup */
    free(current_stage);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    /* Termination */
    return EXIT_SUCCESS;
}
