cmake_minimum_required(VERSION 3.16)

project(pong VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

cmake_policy(SET CMP0135 NEW)

find_package(Qt6 REQUIRED COMPONENTS Core Quick)
qt_standard_project_setup()

add_subdirectory(src/app)
add_subdirectory(src/game)
add_subdirectory(tests)