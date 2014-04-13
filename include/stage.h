#ifndef STAGE_H
#define STAGE_H

#include "SDL.h"

struct stage;
struct stage_vtable {
    void (*handle_event)(const struct stage *this, SDL_Event *event);
    void (*handle_network)(const struct stage *this);
    void (*update)(const struct stage *this);
    void (*render)(const struct stage *this, SDL_Renderer *renderer);
};

struct stage {
    struct stage_vtable *vtable;
};

void stage_handle_event(const struct stage *this, SDL_Event *event);
void stage_handle_network(const struct stage *this);
void stage_render(const struct stage *this, SDL_Renderer *renderer);
void stage_update(const struct stage *this);

#endif /* STAGE_H */
