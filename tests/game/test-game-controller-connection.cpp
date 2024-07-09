//
// Created by kperdek8 on 26.06.2024.
//
#include "GameController.h" // Include the header for GameController
#include <cassert>
#include <gtest/gtest.h>
#include <vector>

// Define a test fixture for GameController tests if needed
class GameControllerTest : public ::testing::Test {
protected:
  void SetUp() override {
    // Initialize any common objects or setup steps
  }

  void TearDown() override {
    // Clean up after each test
  }

  // Define any helper functions or variables specific to the fixture
};

TEST_F(GameControllerTest, AttachDetachTest) {
  GameController controller;
  std::vector<std::weak_ptr<Connection> > connections;

  // Attach first connection
  std::optional<std::weak_ptr<Connection> > attachment1 = controller.attach();
  ASSERT_TRUE(attachment1.has_value());
  connections.push_back(attachment1.value());

  // Attach second connection
  std::optional<std::weak_ptr<Connection> > attachment2 = controller.attach();
  ASSERT_TRUE(attachment2.has_value());
  connections.push_back(attachment2.value());

  // Attempt to attach third connection (should fail)
  std::optional<std::weak_ptr<Connection> > attachment3 = controller.attach();
  ASSERT_FALSE(attachment3.has_value());

  // Detach connection with id 0
  controller.detach(connections[0].lock());
  ASSERT_EQ(controller.getConnectionCount(), 1);

  // Attach another connection (should succeed after detachment)
  std::optional<std::weak_ptr<Connection> > attachment4 = controller.attach();
  ASSERT_TRUE(attachment4.has_value());
  connections.push_back(attachment4.value());
}

// Test case for GameController::attach() method
TEST_F(GameControllerTest, AttachTest) {
  GameController controller;
  // Test attaching connections
  auto connection1 = controller.attach();
  auto connection2 = controller.attach();
  auto connection3 = controller.attach();

  ASSERT_TRUE(connection1.has_value());
  ASSERT_TRUE(connection2.has_value());
  ASSERT_FALSE(connection3.has_value()); // Should fail as there are only 2 slots

  // Verify connection count after attachments
  ASSERT_EQ(controller.getConnectionCount(), 2);
}

// Test case for GameController::detach() method
TEST_F(GameControllerTest, DetachTest) {
  GameController controller;
  // Attach a connection
  auto connection = controller.attach();
  ASSERT_TRUE(connection.has_value());

  // Detach the connection
  controller.detach(connection.value());

  // Verify connection count after detachment
  ASSERT_EQ(controller.getConnectionCount(), 0);
}

// Test case for GameController::isConnectionAvailable() method
TEST_F(GameControllerTest, IsConnectionAvailableTest) {
  GameController controller;
  // Initially, there should be empty slots available
  ASSERT_TRUE(controller.isConnectionAvailable());

  // Fill up all connection slots
  controller.attach();
  controller.attach();

  // No more slots available
  ASSERT_FALSE(controller.isConnectionAvailable());
}

// Entry point for running all tests
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
