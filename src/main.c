#include "main.h"

int main(int argc, char **argv)
{
    struct stage *current_stage;

    /* Load libraries */
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_EVENTS);
    
    /* Optain library versions */
    /*
    SDL_version compiled;
    SDL_version linked;
    SDL_VERSION(&compiled);
    SDL_GetVersion(&linked);
    printf("SDL version compiled: %d.%d.%d\n", compiled.major, compiled.minor, compiled.patch);
    printf("SDL version linked: %d.%d.%d\n", linked.major, linked.minor, linked.patch);
    */

    /* Create window and renderer */
    SDL_Window      *window;
    SDL_Renderer    *renderer;
    SDL_DisplayMode  mode;

    SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP, &window, &renderer);
    SDL_GetCurrentDisplayMode(0, &mode);

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
    stage_game_load(renderer);
    stage_game_init((struct stage_game *)current_stage);

    push_render_event(0, NULL);
    
    /* Main loop */
    SDL_Event event;
    while (1) {
        if (!SDL_WaitEvent(&event)) {
            fprintf(stderr, "Could not wait for event: %s\n", SDL_GetError());
            return EXIT_FAILURE;
        }

        switch (event.type) {
            case SDL_USEREVENT:
                if (event.user.code == EVENTCODE_RENDER) {
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
                    SDL_RenderClear(renderer);
                    stage_update(current_stage);
                    stage_render(current_stage, renderer);
                    SDL_RenderPresent(renderer);
                    
                    SDL_AddTimer(10, push_render_event, NULL);
                }
                break;
            default:
                stage_handle_event(current_stage, &event);
                break;
        }
    }

    /* Cleanup */
    stage_game_unload();
    free(current_stage);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    /* Termination */
    return EXIT_SUCCESS;
}

Uint32 push_render_event(Uint32 interval, void *param)
{
    SDL_Event event;
    SDL_UserEvent userevent;

    userevent.type = SDL_USEREVENT;
    userevent.code = EVENTCODE_RENDER;
    userevent.data1 = NULL;
    userevent.data2 = NULL;

    event.type = SDL_USEREVENT;
    event.user = userevent;

    SDL_PushEvent(&event);
    return 0;
}
