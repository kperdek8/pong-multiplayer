add_executable(pong app.cpp)

target_link_libraries(pong PRIVATE
                      GameLib
                      RenderLib
                      SDL3::SDL3-static)