//
// Created by kperdek8 on 02.07.2024.
//
#include <gtest/gtest.h>
#include "GameObjects.h"
#include "GameField.h"

class BallTest : public ::testing::Test {
protected:
  BallTest() : ball() {}
  Ball ball;
};

TEST_F(BallTest, InitialPosition) {
  EXPECT_FLOAT_EQ(ball.getX(), 0.0f);
  EXPECT_FLOAT_EQ(ball.getY(), 0.0f);
}

TEST_F(BallTest, MovePosition) {
  ball.move(Vector2D{5.0f, 10.0f});
  EXPECT_FLOAT_EQ(ball.getX(), 5.0f);
  EXPECT_FLOAT_EQ(ball.getY(), 10.0f);
}

TEST_F(BallTest, ResetPosition) {
  ball.move(Vector2D{5.0f, 10.0f});
  ball.start(Side::LEFT);
  ball.resetPosition();
  EXPECT_FLOAT_EQ(ball.getX(), GameField::width / 2.0f);
  EXPECT_FLOAT_EQ(ball.getY(), GameField::height / 2.0f);
  EXPECT_FLOAT_EQ(ball.getVelX(), 0.0f);
  EXPECT_FLOAT_EQ(ball.getVelY(), 0.0f);
}

TEST_F(BallTest, Start) {
  ball.start(Side::LEFT);
  EXPECT_GT(ball.getVelX(), 0.0f);

  ball.resetPosition();
  ball.start(Side::RIGHT);
  EXPECT_LT(ball.getVelX(), 0.0f);
}

TEST_F(BallTest, Bounce) {
  ball.start(Side::LEFT);

  float velY = ball.getVelY();
  ball.bounce(Direction::TOP);
  EXPECT_FLOAT_EQ(ball.getVelY(), -velY);

  velY = ball.getVelY();
  ball.bounce(Direction::BOTTOM);
  EXPECT_FLOAT_EQ(ball.getVelY(), -velY);

  float velX = ball.getVelX();
  ball.bounce(Direction::RIGHT);
  EXPECT_FLOAT_EQ(ball.getVelX(), -velX);

  velX = ball.getVelX();
  ball.bounce(Direction::LEFT);
  EXPECT_FLOAT_EQ(ball.getVelX(), -velX);

}
