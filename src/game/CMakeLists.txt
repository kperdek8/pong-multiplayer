qt_add_library(GameLib SHARED
               GameController.cpp
               GameController.h
               GameObjects.cpp
               GameObjects.h
               Connection.cpp
               Connection.h
               Action.h
               GameState.cpp
               GameState.h
               Direction.h
               GameField.h
               Vector2D.h
)

target_link_libraries(GameLib PRIVATE
                      Qt6::Core
                      Qt6::Quick
)
target_include_directories(GameLib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})