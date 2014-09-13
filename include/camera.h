#ifndef CAMERA_H
#define CAMERA_H

#include "common.h"
#include "chunk.h"
#include "engine.h"
#include "tile.h"

struct camera {
    int world_chunk_x;
    int world_chunk_y; 
    unsigned int chunk_cell_x;
    unsigned int chunk_cell_y;
};

void camera_load(void);
void camera_unload(void);
void camera_up(void);
void camera_down(void);
void camera_left(void);
void camera_right(void);
void camera_render(void);

#endif /* CAMERA_H */
