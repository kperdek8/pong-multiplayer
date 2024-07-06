add_executable(pong main.cpp)

target_link_libraries(pong PRIVATE GameLib
                      SDL3::SDL3-static)