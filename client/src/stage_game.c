#include "stage_game.h"

struct stage_vtable g_stage_game_vtable = {
    .handle_event    = (void (*)(const struct stage *this, SDL_Event *event))&stage_game_handle_event,
    .handle_network  = (void (*)(const struct stage *this))&stage_game_handle_network,
    .render          = (void (*)(const struct stage *this))&stage_game_render,
    .update          = (void (*)(const struct stage *this))&stage_game_update
};

void stage_game_handle_event(const struct stage_game *this, SDL_Event *event)
{
    switch (event->type) {
        case SDL_KEYDOWN:
            if (event->key.keysym.sym == SDLK_ESCAPE) exit(1); /* FIXME: proper cleanup */
    }
}

void stage_game_handle_network(const struct stage_game *this)
{
    /* TODO: impl */
}

void stage_game_render(const struct stage_game *this)
{
    /* TODO: impl */
}

void stage_game_update(const struct stage_game *this)
{
    /* TODO: impl */
}

void stage_game_init(struct stage_game *this)
{
    this->stage.vtable = &g_stage_game_vtable;
}
