cmake_minimum_required(VERSION 3.16)

project(pong VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(SDL_SHARED "SDL_SHARED" ON)
option(SDL_STATIC "SDL_STATIC" ON)

cmake_policy(SET CMP0135 NEW)

include(FetchContent)

# Fetch SDL3
FetchContent_Declare(
        SDL3
        GIT_REPOSITORY https://github.com/libsdl-org/SDL
        GIT_TAG origin/main
)
FetchContent_MakeAvailable(SDL3)

include_directories(${sdl3_SOURCE_DIR}/include)
include_directories(${sdl3_BINARY_DIR})

FetchContent_Declare(
        SDL3_net
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_net.git
        GIT_TAG main
)
FetchContent_MakeAvailable(SDL3_net)
include_directories(${SDL3_net_SOURCE_DIR}/include)

add_subdirectory(src)
add_subdirectory(tests)