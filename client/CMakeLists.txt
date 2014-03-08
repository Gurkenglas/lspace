CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(client)

INCLUDE_DIRECTORIES(
    ../lib/SDL/include
    ../common/include
    include
)

ADD_EXECUTABLE(
    client
    src/main.c
)

TARGET_LINK_LIBRARIES(
    client
    common
    SDL2
)
