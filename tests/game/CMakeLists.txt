add_executable(GameModuleTest test-game-controller.cpp)

target_link_libraries(GameModuleTest PRIVATE GameLib GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(GameModuleTest)