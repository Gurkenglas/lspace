#include "stage_game.h"

void stage_game_handle_keyboard(const struct stage_game *this)
{
    /* TODO: impl */
}

void stage_game_handle_mouse(const struct stage_game *this)
{
    /* TODO: impl */
}

void stage_game_handle_event(const struct stage_game *this)
{
    /* TODO: impl */
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
