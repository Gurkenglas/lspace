CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(lspace)

ADD_SUBDIRECTORY(lib/SDL)

INCLUDE_DIRECTORIES(
    lib/SDL/include
    lib/SDL_image
    include
)

ADD_SUBDIRECTORY(lib/SDL_image)

ADD_DEFINITIONS(
    -std=c99
    -pedantic
    -Wall
    -Werror
)

ADD_EXECUTABLE(
    lspace
    src/engine.c
    src/main.c
    src/stage.c
    src/stage_game.c
)

TARGET_LINK_LIBRARIES(
    lspace
    SDL2-static
    SDL2_image
)
