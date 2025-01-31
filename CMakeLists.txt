cmake_minimum_required(VERSION 3.16)

project(pong VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
option(SDL_SHARED "SDL_SHARED" OFF)
option(SDL_STATIC "SDL_STATIC" ON)

cmake_policy(SET CMP0135 NEW)

include(FetchContent)

# Find/Fetch SDL3
find_package(SDL3 QUIET)
if (NOT SDL3_FOUND)
  message(STATUS "SDL3 not found, using FetchContent to download it.")
  FetchContent_Declare(
          SDL3
          GIT_REPOSITORY https://github.com/libsdl-org/SDL
          GIT_TAG origin/main
  )

  FetchContent_MakeAvailable(SDL3)
endif ()

include_directories(${sdl3_SOURCE_DIR}/include)
include_directories(${sdl3_BINARY_DIR})

FetchContent_Declare(
        asio
        GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
        GIT_TAG asio-1-30-2
)

FetchContent_MakeAvailable(asio)
include_directories(${asio_SOURCE_DIR}/asio/include)


add_subdirectory(src)
add_subdirectory(tests)