set(INPUT_SOURCES
    InputHandler.cpp
    KeyMapping.cpp
)

set(INPUT_HEADERS
    InputHandler.h
    KeyMapping.h
)

add_library(InputLib ${INPUT_SOURCES} ${INPUT_HEADERS})
set_target_properties(InputLib PROPERTIES PREFIX "")
target_link_libraries(InputLib PRIVATE SDL3::SDL3-static
                      GameLib)
target_include_directories(InputLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})