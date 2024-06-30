//
// Created by kperdek8 on 25.06.2024.
//

#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H

#include "Direction.h"
#include "GameField.h"
#include <random>

enum class Side { LEFT = 0, RIGHT = 1 };

class GameObject {
public:
  const float width, height;
  [[nodiscard]] float getX() const { return x_; };
  [[nodiscard]] float getY() const { return x_; };

  GameObject(const float width, const float height)
      : width{width}, height{height} {}
  GameObject(const float width, const float height, const float x,
             const float y)
      : width{width}, height{height}, x_{x}, y_{y} {}
  virtual ~GameObject() = default;

  virtual void resetPosition() = 0;

  [[nodiscard]] Direction boundsCollision(float xMovement,
                                          float yMovement) const;

  [[nodiscard]] bool objectCollision(const GameObject &, float xMovement,
                                     float yMovement) const;

  void update(float dt);

protected:
  float x_ = 0.0f, y_ = 0.0f;
  float xVelocity_ = 0.0f, yVelocity_ = 0.0f;
};

class Paddle final : public GameObject {
public:
  static constexpr float WIDTH = 50.0f;
  static constexpr float HEIGHT = 300.0f;
  static constexpr float MAX_VELOCITY = 50.0f;

  Paddle() : GameObject(WIDTH, HEIGHT) {}
  Paddle(const float x, const float y) : GameObject(WIDTH, HEIGHT, x, y) {}

  void resetPosition() override;
  void addVelocity(float yVel);
};

class Ball final : public GameObject {
public:
  static constexpr float WIDTH = 50.0f;
  static constexpr float HEIGHT = 50.0f;
  static constexpr float INITIAL_VELOCITY = 50.0f;
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
  explicit Player(const int id) : id(id) {}

  int id;
  int points = 0;
  Side side = id ? Side::RIGHT : Side::LEFT; // Player with id 0 on the left
  Paddle paddle{};
};

#endif // GAMEOBJECTS_H
