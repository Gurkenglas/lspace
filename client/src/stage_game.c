#include "stage_game.h"

void stage_game_handle_keyboard(struct stage_game *this)
{
    /* TODO: impl */
}

void stage_game_handle_mouse(struct stage_game *this)
{
    /* TODO: impl */
}

void stage_game_handle_event(struct stage_game *this)
{
    /* TODO: impl */
}

void stage_game_handle_network(struct stage_game *this)
{
    /* TODO: impl */
}

void stage_game_render(struct stage_game *this)
{
    /* TODO: impl */
}

void stage_game_update(struct stage_game *this)
{
    /* TODO: impl */
}

void stage_game_init(struct stage_game *this)
{
    this->stage.vtable = &g_stage_game_vtable;
}
