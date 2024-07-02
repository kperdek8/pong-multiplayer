//
// Created by kperdek8 on 02.07.2024.
//
#include <gtest/gtest.h>
#include "GameField.h"
#include "Vector2D.h"
#include "Direction.h"
#include "GameObjects.h"

// Create simple implementation of abstract class GameObject
class TestGameObject final : public GameObject {
public:
  TestGameObject(const float width, const float height) : GameObject(width, height) {}
  TestGameObject(const float width, const float height, const float x, const float y) : GameObject(width, height, x, y) {}
  void resetPosition() override {
    position_ = Vector2D{0.0f, 0.0f};
  }
};

class GameObjectTest : public ::testing::Test {
protected:
  GameObjectTest() : gameObject(20.0f, 20.0f) {}
  TestGameObject gameObject;
};

TEST_F(GameObjectTest, InitialPosition) {
  EXPECT_FLOAT_EQ(gameObject.getX(), 0.0f);
  EXPECT_FLOAT_EQ(gameObject.getY(), 0.0f);
}

TEST_F(GameObjectTest, MovePosition) {
  gameObject.move(Vector2D{5.0f, 10.0f});
  EXPECT_FLOAT_EQ(gameObject.getX(), 5.0f);
  EXPECT_FLOAT_EQ(gameObject.getY(), 10.0f);
}

TEST_F(GameObjectTest, BoundsCollision) {
  // Origin "hitbox"
  EXPECT_EQ(gameObject.boundsCollision(Vector2D{-1.0f, 0.0f}), Direction::LEFT);
  EXPECT_EQ(gameObject.boundsCollision(Vector2D{GameField::width+1.0f, 0.0f}), Direction::RIGHT);
  EXPECT_EQ(gameObject.boundsCollision(Vector2D{0.0f, -1.0f}), Direction::BOTTOM);
  EXPECT_EQ(gameObject.boundsCollision(Vector2D{0.0f, GameField::height+1.0f}), Direction::TOP);
  // Closest edge "hitbox"
  EXPECT_EQ(gameObject.boundsCollision(Vector2D{-1.0f, 0.0f}), Direction::LEFT);
  EXPECT_EQ(gameObject.boundsCollision(Vector2D{GameField::width-gameObject.width+1.0f, 0.0f}), Direction::RIGHT);
  EXPECT_EQ(gameObject.boundsCollision(Vector2D{0.0f, -1.0f}), Direction::BOTTOM);
  EXPECT_EQ(gameObject.boundsCollision(Vector2D{0.0f, GameField::height-gameObject.height+1.0f}), Direction::TOP);
  // Close, but not colliding
  EXPECT_NE(gameObject.boundsCollision(Vector2D{0.01f, 0.0f}), Direction::LEFT);
  EXPECT_NE(gameObject.boundsCollision(Vector2D{GameField::width-gameObject.width-0.01f, 0.0f}), Direction::RIGHT);
  EXPECT_NE(gameObject.boundsCollision(Vector2D{0.0f, 0.01f}), Direction::BOTTOM);
  EXPECT_NE(gameObject.boundsCollision(Vector2D{0.0f, GameField::height-gameObject.height-0.01f}), Direction::TOP);
}

TEST_F(GameObjectTest, ObjectCollision) {
  const TestGameObject otherObject(20.0f, 20.0f, 25.0f, 25.0f);
  // Check if single axis overlap is properly ignored
  EXPECT_EQ(gameObject.objectCollision(otherObject, Vector2D{0.0f, 6.0f}), Direction::NONE);
  EXPECT_EQ(gameObject.objectCollision(otherObject, Vector2D{6.0f, 0.0f}), Direction::NONE);
  EXPECT_EQ(gameObject.objectCollision(otherObject, Vector2D{0.0f, 26.0f}), Direction::NONE);
  EXPECT_EQ(gameObject.objectCollision(otherObject, Vector2D{26.0f, 0.0f}), Direction::NONE);

  // Approach object from below
  gameObject.resetPosition();
  gameObject.move(Vector2D{15.0f,0.0f});
  EXPECT_EQ(gameObject.objectCollision(otherObject, Vector2D{0.0f, 4.99f}), Direction::NONE);
  EXPECT_EQ(gameObject.objectCollision(otherObject, Vector2D{0.0f, 6.0f}), Direction::TOP);

  // Approach object from the left
  gameObject.resetPosition();
  gameObject.move(Vector2D{0.0f,15.0f});
  EXPECT_EQ(gameObject.objectCollision(otherObject, Vector2D{4.99f, 0.0f}), Direction::NONE);
  EXPECT_EQ(gameObject.objectCollision(otherObject, Vector2D{6.0f, 0.0f}), Direction::RIGHT);

  // Approach object from above
  gameObject.resetPosition();
  gameObject.move(Vector2D{15.0f,50.0f});
  EXPECT_EQ(gameObject.objectCollision(otherObject, Vector2D{0.0f, -4.99f}), Direction::NONE);
  EXPECT_EQ(gameObject.objectCollision(otherObject, Vector2D{0.0f, -6.0f}), Direction::BOTTOM);

  // Approach object from the right
  gameObject.resetPosition();
  gameObject.move(Vector2D{50.0f,15.0f});
  EXPECT_EQ(gameObject.objectCollision(otherObject, Vector2D{-4.99f, 0.0f}), Direction::NONE);
  EXPECT_EQ(gameObject.objectCollision(otherObject, Vector2D{-6.0f, 0.0f}), Direction::LEFT);


}