add_executable(pong app.cpp)

target_link_libraries(pong PRIVATE
                      GameLib
                      InputLib
                      RenderLib
                      NetworkLib
                      SDL3::SDL3)