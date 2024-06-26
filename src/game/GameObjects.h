//
// Created by kperdek8 on 25.06.2024.
//

#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H

struct Paddle {
  float x,y;
  float velocity;
};

struct Player {
  explicit Player(const int id) : id(id) {}
  int id;
  int points = 0;
  Paddle paddle{};
};

#endif //GAMEOBJECTS_H
