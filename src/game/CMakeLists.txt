set(GAME_SOURCES
    GameController.cpp
    GameObjects.cpp
    GameState.cpp
)

set(GAME_HEADERS
    GameController.h
    GameObjects.h
    Action.h
    GameState.h
    Direction.h
    GameField.h
    Vector2D.h
)

add_library(GameLib ${GAME_SOURCES} ${GAME_HEADERS})
set_target_properties(GameLib PROPERTIES PREFIX "")
target_include_directories(GameLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})