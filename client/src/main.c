#include "main.h"

int main(int argc, const char **argv)
{
    struct stage *current_stage;

    /* Load libraries */
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO);
    
    /* Optain library versions */
    SDL_version compiled;
    SDL_version linked;
    SDL_VERSION(&compiled);
    SDL_GetVersion(&linked);
    printf("SDL version compiled: %d.%d.%d\n", compiled.major, compiled.minor, compiled.patch);
    printf("SDL version linked: %d.%d.%d\n", linked.major, linked.minor, linked.patch);

    /* Create window and renderer */
    SDL_Window      *window;
    SDL_Renderer    *renderer;
    SDL_DisplayMode  mode;

    SDL_GetCurrentDisplayMode(0, &mode);
    SDL_CreateWindowAndRenderer(mode.w, mode.h, SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_OPENGL, &window, &renderer);

    if (!window) {
        fprintf(stderr, "Could not create window and renderer: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    /* Change stage to game */
    current_stage = malloc(sizeof (struct stage_game));
    if (!current_stage) {
        fprintf(stderr, "Could not allocate game stage\n");
        return EXIT_FAILURE;
    }
    stage_game_init((struct stage_game *)current_stage);
    
    /* Main loop */
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

    SDL_Event event;
    while (1) {
        int ok = SDL_WaitEvent(&event);
        if (!ok) {
            fprintf(stderr, "Could not wait for event: %s\n", SDL_GetError());
        }

        stage_handle_event(current_stage, &event);
        SDL_RenderClear(renderer);
        stage_update(current_stage);
        stage_render(current_stage);
        SDL_RenderPresent(renderer);
    }

    SDL_Delay(3000);

    /* Cleanup */
cleanup:
    free(current_stage);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    /* Termination */
    return EXIT_SUCCESS;
}
