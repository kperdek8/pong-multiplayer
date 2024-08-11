add_executable(pong app.cpp Game.cpp Game.h)

target_link_libraries(pong PRIVATE
                      GameLib
                      InputLib
                      RenderLib
                      NetworkLib
                      SDL3::SDL3)