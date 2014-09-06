#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include "eventcode.h"
#include "stage.h"
#include "stage_game.h"
#include "SDL.h"

int main(int argc, char **argv);
Uint32 push_render_event(Uint32 interval, void *param);

#endif /* MAIN_H */
