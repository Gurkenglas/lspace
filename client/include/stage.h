#ifndef STAGE_H
#define STAGE_H

struct stage;
struct stage_vtable {
    void (*handle_event)(struct stage *this);
    void (*handle_keyboard)(struct stage *this);
    void (*handle_mouse)(struct stage *this);
    void (*handle_network)(struct stage *this);
    void (*update)(struct stage *this);
    void (*render)(struct stage *this);
};

struct stage {
    struct stage_vtable *vtable;
};

void stage_handle_event(struct stage *this);
void stage_handle_keyboard(struct stage *this);
void stage_handle_mouse(struct stage *this);
void stage_handle_network(struct stage *this);
void stage_render(struct stage *this);
void stage_update(struct stage *this);

#endif /* STAGE_H */
