cmake_minimum_required(VERSION 3.10)
project(CommonLib)

set(COMMON_HEADERS
    Action.h
    ConnectionType.h
    Data.h
    Vector2D.h
)

add_library(CommonLib INTERFACE ${COMMON_HEADERS})
target_include_directories(CommonLib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(CommonLib PROPERTIES PREFIX "")