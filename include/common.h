#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "SDL.h"

#include "eventcode.h"

bool g_render_event_queued;

void push_render_event(void);

#endif /* COMMON_H */
