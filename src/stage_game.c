#include "stage_game.h"

SDL_Texture *g_texture;
    
/* to clean */

struct stage_vtable g_stage_game_vtable = {
    .load            = (void (*)(struct stage *this)) stage_game_load, 
    .unload          = (void (*)(struct stage *this)) stage_game_unload, 
    .handle_event    = (void (*)(const struct stage *this, SDL_Event *event)) stage_game_handle_event,
    .handle_network  = (void (*)(const struct stage *this)) stage_game_handle_network,
    .render          = (void (*)(const struct stage *this)) stage_game_render,
    .update          = (void (*)(const struct stage *this)) stage_game_update,
};

void stage_game_handle_event(const struct stage_game *this, SDL_Event *event)
{
    /* TODO: impl */
    switch (event->type) {
        case SDL_KEYDOWN:
            if (event->key.keysym.sym == SDLK_ESCAPE) exit(EXIT_SUCCESS);
            else if (event->key.keysym.sym == SDLK_UP) camera_up();
            else if (event->key.keysym.sym == SDLK_DOWN) camera_down();
            else if (event->key.keysym.sym == SDLK_LEFT) camera_left();
            else if (event->key.keysym.sym == SDLK_RIGHT) camera_right();
            break;
    }
}

void stage_game_handle_network(const struct stage_game *this)
{
    /* TODO: impl */
}

void stage_game_render(const struct stage_game *this)
{
    camera_render();
}

void stage_game_update(const struct stage_game *this)
{
    /* TODO: impl */
}

void stage_game_init(struct stage_game *this)
{
    this->stage.vtable = &g_stage_game_vtable;
}

void stage_game_load(struct stage_game *this)
{
    camera_load();
}

void stage_game_unload(struct stage_game *this)
{
    camera_unload();
}
