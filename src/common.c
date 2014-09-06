#include "common.h"

bool g_render_event_queued = false;

void push_render_event(void)
{
    /*
     * Push a render event only if one isn't already queued.
     * It let us only update the screen when there's something new to show by calling this function, otherwise, idling.
     * It also let us call this function as often as we want while still doing only one rendering pass in the end.
     * Pretty nifty optimization.
     */
    if (!g_render_event_queued) {
        g_render_event_queued = true;

        SDL_Event event;
        SDL_UserEvent userevent;

        userevent.type = SDL_USEREVENT;
        userevent.code = EVENTCODE_RENDER;
        userevent.data1 = NULL;
        userevent.data2 = NULL;

        event.type = SDL_USEREVENT;
        event.user = userevent;

        SDL_PushEvent(&event);
    }
}
