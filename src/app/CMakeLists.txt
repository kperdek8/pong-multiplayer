add_executable(pong_server network_server.cpp)
add_executable(pong_client network_client.cpp)

target_link_libraries(pong_server PRIVATE
                      NetworkLib
                      SDL3::SDL3)

target_link_libraries(pong_client PRIVATE
                      NetworkLib
                      SDL3::SDL3)