#ifndef STAGE_GAME_H
#define STAGE_GAME_H

#include "stage.h"

struct stage_game {
    struct stage stage;
};

void stage_game_handle_event(const struct stage_game *this);
void stage_game_handle_keyboard(const struct stage_game *this);
void stage_game_handle_mouse(const struct stage_game *this);
void stage_game_handle_network(const struct stage_game *this);
void stage_game_init(struct stage_game *this);
void stage_game_render(const struct stage_game *this);
void stage_game_update(const struct stage_game *this);

#endif /* STAGE_GAME_H */
