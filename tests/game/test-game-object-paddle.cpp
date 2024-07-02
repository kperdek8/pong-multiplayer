//
// Created by kperdek8 on 02.07.2024.
//
#include <gtest/gtest.h>
#include "GameObjects.h"
#include "GameField.h"

class PaddleTest : public ::testing::Test {
protected:
  PaddleTest() : paddle() {}
  Paddle paddle;
};

TEST_F(PaddleTest, InitialPosition) {
  EXPECT_FLOAT_EQ(paddle.getX(), 0.0f);
  EXPECT_FLOAT_EQ(paddle.getY(), 0.0f);
}

TEST_F(PaddleTest, MovePosition) {
  paddle.move(Vector2D{0.0f, 10.0f});
  EXPECT_FLOAT_EQ(paddle.getY(), 10.0f);
}

TEST_F(PaddleTest, AddVelocity) {
  paddle.addVelocity(Vector2D{0.0f, 10.0f});
  EXPECT_FLOAT_EQ(paddle.getVelY(), 10.0f);

  paddle.addVelocity(Vector2D{0.0f, 50.0f});
  EXPECT_FLOAT_EQ(paddle.getVelY(), Paddle::MOVESPEED);
}

TEST_F(PaddleTest, SetVelocity) {
  paddle.setVelocity(Vector2D{0.0f, 30.0f});
  EXPECT_FLOAT_EQ(paddle.getVelY(), 30.0f);
}

TEST_F(PaddleTest, ResetPosition) {
  paddle.move(Vector2D{0.0f, 10.0f});
  paddle.resetPosition();
  EXPECT_FLOAT_EQ(paddle.getY(), GameField::height / 2.0f);
}