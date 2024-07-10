add_executable(pong app.cpp)

target_link_libraries(pong PRIVATE
                      GameLib
                      RenderLib
                      InputLib)