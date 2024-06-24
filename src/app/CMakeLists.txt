qt_add_executable(pong
                  main.cpp
)

target_link_libraries(pong PRIVATE
                      Qt6::Core
#                     Qt6::Widgets
)