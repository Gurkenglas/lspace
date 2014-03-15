#ifndef STAGE_GAME_H
#define STAGE_GAME_H

#include "stage.h"

struct stage_game {
    struct stage stage;
};

void stage_game_handle_event(struct stage_game *this);
void stage_game_handle_keyboard(struct stage_game *this);
void stage_game_handle_mouse(struct stage_game *this);
void stage_game_handle_network(struct stage_game *this);
void stage_game_init(struct stage_game *this);
void stage_game_render(struct stage_game *this);
void stage_game_update(struct stage_game *this);

struct stage_vtable g_stage_game_vtable = {
    .handle_event    = (void (*)(struct stage *this))&stage_game_handle_event,
    .handle_keyboard = (void (*)(struct stage *this))&stage_game_handle_keyboard,
    .handle_mouse    = (void (*)(struct stage *this))&stage_game_handle_mouse,
    .handle_network  = (void (*)(struct stage *this))&stage_game_handle_network,
    .render          = (void (*)(struct stage *this))&stage_game_render,
    .update          = (void (*)(struct stage *this))&stage_game_update
};


#endif /* STAGE_GAME_H */
