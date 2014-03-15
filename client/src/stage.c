#include "stage.h"

void handle_event(const struct stage *this)
{
    this->vtable->handle_event(this);
}

void handle_keyboard(const struct stage *this)
{
    this->vtable->handle_keyboard(this);
}

void handle_mouse(const struct stage *this)
{
    this->vtable->handle_mouse(this);
}

void handle_network(const struct stage *this)
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

