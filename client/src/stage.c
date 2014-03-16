#include "stage.h"

void stage_handle_event(const struct stage *this, SDL_Event *event)
{
    this->vtable->handle_event(this, event);
}

void stage_handle_network(const struct stage *this)
{
    this->vtable->handle_network(this);
}

void stage_render(const struct stage *this)
{
    this->vtable->render(this);
}
void stage_update(const struct stage *this)
{
    this->vtable->update(this);
}
