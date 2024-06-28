//
// Created by kperdek8 on 25.06.2024.
//

#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H

struct GameField {
  constexpr static float width = 1920;
  constexpr static float height = 1080;
};

struct Paddle {
  float x, y;
  float velocity;

  void resetPosition() {
    y = GameField::height / 2.0f;
  };
};

struct Ball {
  float x, y;
  float xVelocity;
  float yVelocity;

  void resetPosition() {
    x = GameField::width / 2.0f;
    y = GameField::height / 2.0f;
  };
};

enum Side { LEFT = 0, RIGHT = 1 };

struct Player {
  explicit Player(const int id) : id(id) {}

  int id;
  int points = 0;
  Side side = id ? RIGHT : LEFT; // Player with id 0 on the left
  Paddle paddle{};
};

#endif // GAMEOBJECTS_H
