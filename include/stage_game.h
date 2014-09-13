#ifndef STAGE_GAME_H
#define STAGE_GAME_H

#include "common.h"
#include "camera.h"
#include "chunk.h"
#include "engine.h"
#include "stage.h"
#include "tile.h"

struct stage_game {
    struct stage stage;
};

void stage_game_handle_event(const struct stage_game *this, SDL_Event *event);
void stage_game_handle_network(const struct stage_game *this);
void stage_game_init(struct stage_game *this);
void stage_game_load(struct stage_game *this);
void stage_game_render(const struct stage_game *this);
void stage_game_unload(struct stage_game *this);
void stage_game_update(const struct stage_game *this);

#endif /* STAGE_GAME_H */
