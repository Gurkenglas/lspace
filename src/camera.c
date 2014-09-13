#include "camera.h"

struct camera g_camera;

void camera_load(void)
{
}

void camera_unload(void)
{
}

void camera_up(void)
{
    if (g_camera.chunk_cell_y == 0) {
        g_camera.chunk_cell_y = CHUNK_SIZE - 1;
        g_camera.world_chunk_y--;
    } else {
        g_camera.chunk_cell_y--;
    }
    
    engine_reschedule();
}

void camera_down(void)
{
    g_camera.chunk_cell_y++;
    if (g_camera.chunk_cell_y == CHUNK_SIZE) {
        g_camera.chunk_cell_y = 0;
        g_camera.world_chunk_y++;
    }

    engine_reschedule();
}

void camera_left(void)
{
    if (g_camera.chunk_cell_x == 0) {
        g_camera.chunk_cell_x = CHUNK_SIZE - 1;
        g_camera.world_chunk_x--;
    } else {
        g_camera.chunk_cell_x--;
    }

    engine_reschedule();
}

void camera_right(void)
{
    g_camera.chunk_cell_x++;
    if (g_camera.chunk_cell_x == CHUNK_SIZE) {
        g_camera.chunk_cell_x = 0;
        g_camera.world_chunk_x++;
    }

    engine_reschedule();
}

void camera_render(void)
{
    /* +1 for screen dimension rounding errors, another +1 for when reaching chunk limits (moving around) */
    unsigned int camera_chunk_width = g_display.w / (CHUNK_SIZE * TILE_SIZE) + 2;
    unsigned int camera_chunk_height = g_display.h / (CHUNK_SIZE * TILE_SIZE) + 2;

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
                    SDL_RenderCopy(g_renderer, g_texture, &rect_src, &rect_dest);
                }
            }
        }
    }
}
