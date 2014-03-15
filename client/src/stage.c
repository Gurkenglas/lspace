#include "stage.h"

void handle_event(struct stage *this)
{
    this->vtable->handle_event(this);
}

void handle_keyboard(struct stage *this)
{
    this->vtable->handle_keyboard(this);
}

void handle_mouse(struct stage *this)
{
    this->vtable->handle_mouse(this);
}

void handle_network(struct stage *this)
{
    this->vtable->handle_network(this);
}

void stage_render(struct stage *this)
{
    this->vtable->render(this);
}
void stage_update(struct stage *this)
{
    this->vtable->update(this);
}

