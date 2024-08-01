set(RENDERER_SOURCES
    Renderer.cpp
)

set(RENDERER_HEADERS
    Renderer.h
)

add_library(RenderLib ${RENDERER_SOURCES} ${RENDERER_HEADERS})
set_target_properties(RenderLib PROPERTIES PREFIX "")
target_link_libraries(RenderLib PRIVATE SDL3::SDL3
                      GameLib)
target_include_directories(RenderLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})