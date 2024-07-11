//
// Created by kperdek8 on 25.06.2024.
//

#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H

#include <iostream>

#include "Direction.h"
#include "GameField.h"
#include "Vector2D.h"
#include <random>

enum class Side { LEFT = 0, RIGHT = 1 };

class GameObject {
public:
  const float width, height;
  [[nodiscard]] Vector2D getPos() const { return position_; };
  [[nodiscard]] float getX() const { return position_.x; };
  [[nodiscard]] float getY() const { return position_.y; };

  [[nodiscard]] Vector2D getVel() const { return velocity_; };
  [[nodiscard]] float getVelX() const { return velocity_.x; };
  [[nodiscard]] float getVelY() const { return velocity_.y; };

  GameObject(const float width, const float height)
    : width{width}, height{height} {
  }

  GameObject(const float width, const float height, const float x,
             const float y)
    : width{width}, height{height}, position_{x, y} {
  }

  virtual ~GameObject() = default;

  virtual void resetPosition() = 0;

  [[nodiscard]] Direction boundsCollision(const Vector2D &movement) const;

  [[nodiscard]] Direction objectCollision(const GameObject &object,
                                          const Vector2D &movement) const;

  [[nodiscard]] Vector2D distanceToBounds(Direction direction) const;

  [[nodiscard]] Vector2D distanceToObject(const GameObject &object) const;

  void move(const Vector2D &movement);

protected:
  Vector2D position_{0.0f, 0.0f};
  Vector2D velocity_{0.0f, 0.0f};
};

class Paddle final : public GameObject {
public:
  static constexpr float WIDTH = 40.0f;
  static constexpr float HEIGHT = 200.0f;
  static constexpr float MOVESPEED = 50.0f;

  Paddle() : GameObject(WIDTH, HEIGHT) {
  }

  Paddle(const float x, const float y) : GameObject(WIDTH, HEIGHT, x, y) {
  }

  void resetPosition() override;

  void addVelocity(const Vector2D &velocity);

  void setVelocity(const Vector2D &velocity);
};

class Ball final : public GameObject {
public:
  static constexpr float WIDTH = 40.0f;
  static constexpr float HEIGHT = 40.0f;
  static constexpr float INITIAL_VELOCITY = 100.0f;
  static constexpr float MAX_ANGLE = 30.0f;

  Ball()
    : GameObject(WIDTH, HEIGHT), gen_{std::mt19937(std::random_device{}())} {
    angleDist_ = std::uniform_real_distribution<float>(
                                                       -MAX_ANGLE * M_PI / 180.0f, MAX_ANGLE * M_PI / 180.0f);
  }

  Ball(const float x, const float y)
    : GameObject(WIDTH, HEIGHT, x, y),
      gen_{std::mt19937(std::random_device{}())} {
    angleDist_ = std::uniform_real_distribution<float>(
                                                       -MAX_ANGLE * M_PI / 180.0f, MAX_ANGLE * M_PI / 180.0f);
  }

  void bounce(Direction direction);

  void start(Side lastGoal);

  void resetPosition() override;

private:
  // For random angle in start() method
  std::mt19937 gen_;
  std::uniform_real_distribution<float> angleDist_;
};

struct Player {
  explicit Player(const int id) : id(id) {
    std::cout<<"Player "<<id<<" paddle's x: "<<this->paddle.getX()<<std::endl;
  }

  static constexpr float MARGIN = 30.0f;
  static constexpr float LEFT_PADDLE_X = MARGIN;
  static constexpr float RIGHT_PADDLE_X = GameField::width - MARGIN - Paddle::WIDTH;
  static constexpr float INITIAL_PADDLE_Y = (GameField::height - Paddle::HEIGHT) / 2.0f;

  int id;
  int points = 0;
  Side side = id ? Side::RIGHT : Side::LEFT; // Player with id 0 on the left
  Paddle paddle = id
                    ? Paddle{RIGHT_PADDLE_X, INITIAL_PADDLE_Y}
                    : Paddle{LEFT_PADDLE_X, INITIAL_PADDLE_Y};
};

#endif // GAMEOBJECTS_H
