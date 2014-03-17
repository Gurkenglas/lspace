CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(client)

INCLUDE_DIRECTORIES(
    ../lib/SDL/include
    ../lib/SDL_image
    ../common/include
    include
)

ADD_EXECUTABLE(
    client
    src/main.c
    src/stage.c
    src/stage_game.c
)

TARGET_LINK_LIBRARIES(
    client
    common
    SDL2-static
    SDL2_image
)
