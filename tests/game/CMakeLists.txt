add_executable(GameModuleTest test-game-controller-connection.cpp
               test-game-object.cpp
               test-game-object-paddle.cpp
               test-game-object-ball.cpp
               test-game-object-ball.cpp)

target_link_libraries(GameModuleTest PRIVATE GameLib GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(GameModuleTest)