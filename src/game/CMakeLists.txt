set(GAME_SOURCES
    GameController.cpp
    GameObjects.cpp
    GameState.cpp
    Game.cpp
)

set(GAME_HEADERS
    GameController.h
    GameObjects.h
    GameState.h
    Direction.h
    GameField.h
    Game.h
)

add_library(GameLib ${GAME_SOURCES} ${GAME_HEADERS})
target_link_libraries(GameLib PRIVATE NetworkLib
                      InputLib
                      RenderLib)
set_target_properties(GameLib PROPERTIES PREFIX "")
target_include_directories(GameLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})