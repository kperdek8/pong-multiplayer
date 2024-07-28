add_executable(pong network_main.cpp)

target_link_libraries(pong PRIVATE
                      NetworkLib
                      SDL3::SDL3
                      SDL3_net::SDL3_net)