#include "main.h"

int main(int argc, const char **argv)
{
    struct stage *current_stage;

    /* Change stage to game */
    current_stage = malloc(sizeof (struct stage_game));
    stage_game_init((struct stage_game *)current_stage);
    
    /* Main loop */
    stage_update(current_stage);
    stage_render(current_stage);

    /* Cleanup */
    free(current_stage);

    /* Termination */
    return 0;
}
