#include "stage_game.h"

SDL_Texture *g_texture;

struct stage_vtable g_stage_game_vtable = {
    .handle_event    = (void (*)(const struct stage *this, SDL_Event *event))&stage_game_handle_event,
    .handle_network  = (void (*)(const struct stage *this))&stage_game_handle_network,
    .render          = (void (*)(const struct stage *this, SDL_Renderer *renderer))&stage_game_render,
    .update          = (void (*)(const struct stage *this))&stage_game_update
};

void stage_game_handle_event(const struct stage_game *this, SDL_Event *event)
{
    switch (event->type) {
        case SDL_KEYDOWN:
            if (event->key.keysym.sym == SDLK_ESCAPE) exit(EXIT_SUCCESS);
    }
}

void stage_game_handle_network(const struct stage_game *this)
{
    /* TODO: impl */
}

void stage_game_render(const struct stage_game *this, SDL_Renderer *renderer)
{
    /* TODO: impl */
    SDL_Rect rect_src  = {.w = 16, .h = 16, .x = 0, .y = 0};
    SDL_Rect rect_dest = {.w = 16, .h = 16, .x = 0, .y = 0};
    SDL_RenderCopy(renderer, g_texture, &rect_src, &rect_dest);
}

void stage_game_update(const struct stage_game *this)
{
    /* TODO: impl */
}

void stage_game_init(struct stage_game *this)
{
    this->stage.vtable = &g_stage_game_vtable;
}

void stage_game_load(SDL_Renderer *renderer)
{
    SDL_Surface *tileset = IMG_Load("tileset.png");
    if (!tileset) {
        fprintf(stderr, "Unable to load tileset: %s\n", IMG_GetError());
        exit(EXIT_FAILURE);
    }

    g_texture = SDL_CreateTextureFromSurface(renderer, tileset);
    if (!tileset) {
        fprintf(stderr, "Unable to create texture from tileset: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    
    SDL_FreeSurface(tileset);
}

void stage_game_unload(void)
{
    //SDL_FreeTexture(g_texture);
}
