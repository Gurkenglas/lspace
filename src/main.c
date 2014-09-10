#include "main.h"

int main(int argc, char **argv)
{
    /* Prepare the engine */
    engine_load();

    /* Create game stage */
    struct stage_game *first_stage = malloc(sizeof (struct stage_game));
    if (!first_stage) {
        FATAL("Could not allocate game stage as first stage");
    }
    stage_game_init(first_stage);

    /* Run engine */
    engine_stage((struct stage *)first_stage);
    engine_run();
    engine_unload();

    /* Termination */
    return EXIT_SUCCESS;
}
