#include "stage_game.h"

SDL_Texture *g_texture;
struct camera g_camera;
    
/* to clean */
#define CHUNK_SIZE 10
#define TILE_SIZE 32

struct stage_vtable g_stage_game_vtable = {
    .handle_event    = (void (*)(const struct stage *this, SDL_Event *event)) stage_game_handle_event,
    .handle_network  = (void (*)(const struct stage *this)) stage_game_handle_network,
    .render          = (void (*)(const struct stage *this, SDL_Renderer *renderer)) stage_game_render,
    .update          = (void (*)(const struct stage *this)) stage_game_update,
};

void stage_game_handle_event(const struct stage_game *this, SDL_Event *event)
{
    /* TODO: impl */
    switch (event->type) {
        case SDL_KEYDOWN:
            if (event->key.keysym.sym == SDLK_ESCAPE) exit(EXIT_SUCCESS);
            else if (event->key.keysym.sym == SDLK_UP) {
                if (g_camera.chunk_cell_y == 0) {
                    g_camera.chunk_cell_y = CHUNK_SIZE - 1;
                    g_camera.world_chunk_y--;
                } else {
                    g_camera.chunk_cell_y--;
                }
            }
            else if (event->key.keysym.sym == SDLK_DOWN) {
                g_camera.chunk_cell_y++;
                if (g_camera.chunk_cell_y == CHUNK_SIZE) {
                    g_camera.chunk_cell_y = 0;
                    g_camera.world_chunk_y++;
                }
            }
            else if (event->key.keysym.sym == SDLK_LEFT) {
                if (g_camera.chunk_cell_x == 0) {
                    g_camera.chunk_cell_x = CHUNK_SIZE - 1;
                    g_camera.world_chunk_x--;
                } else {
                    g_camera.chunk_cell_x--;
                }
            }
            else if (event->key.keysym.sym == SDLK_RIGHT) {
                g_camera.chunk_cell_x++;
                if (g_camera.chunk_cell_x == CHUNK_SIZE) {
                    g_camera.chunk_cell_x = 0;
                    g_camera.world_chunk_x++;
                }
            }
            push_render_event();
            break;
    }
}

void stage_game_handle_network(const struct stage_game *this)
{
    /* TODO: impl */
}

void stage_game_render(const struct stage_game *this, SDL_Renderer *renderer)
{
    /* TODO: impl */
    /* +1 for screen dimension rounding errors, another +1 for when reaching chunk limits (moving around) */
    unsigned int camera_chunk_width = this->stage.window_width / (CHUNK_SIZE * TILE_SIZE) + 2;
    unsigned int camera_chunk_height = this->stage.window_height / (CHUNK_SIZE * TILE_SIZE) + 2;

    /* Rendering each chunk visible by the camera */
    for (unsigned int chunk_x = 0; chunk_x < camera_chunk_width; chunk_x++) {
        for (unsigned int chunk_y = 0; chunk_y < camera_chunk_height; chunk_y++) {
            //fprintf(stderr, "Rendering chunk %d, %d\n", g_camera.world_chunk_x + chunk_x, g_camera.world_chunk_y + chunk_y);

            /* Rendering one chunk by drawing each cell */
            for (unsigned int cell_x = 0; cell_x < CHUNK_SIZE; cell_x++) {
                for (unsigned int cell_y = 0; cell_y < CHUNK_SIZE; cell_y++) {
                    //fprintf(stderr, "\tRendering cell %d, %d\n", cell_x, cell_y);

                    unsigned int final_x = (chunk_x * CHUNK_SIZE * TILE_SIZE) + (cell_x * TILE_SIZE) - (g_camera.chunk_cell_x * TILE_SIZE);
                    unsigned int final_y = (chunk_y * CHUNK_SIZE * TILE_SIZE) + (cell_y * TILE_SIZE) - (g_camera.chunk_cell_y * TILE_SIZE);

                    /* Rendering one cell */
                    SDL_Rect rect_src = {
                        .w = 32,
                        .h = 32,
                        .x = (g_camera.world_chunk_x + chunk_x) * TILE_SIZE,
                        .y = (g_camera.world_chunk_y + chunk_y) * TILE_SIZE
                    };
                    SDL_Rect rect_dest = {.w = 32, .h = 32, .x = final_x, .y = final_y};
                    SDL_RenderCopy(renderer, g_texture, &rect_src, &rect_dest);
                }
            }
        }
    }
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
