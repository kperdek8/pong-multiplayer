//
// Created by kperdek8 on 30.06.2024.
//

#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "GameObjects.h"
#include <array>
#include <cstddef>
#include <utility>

constexpr std::size_t MAX_PLAYERS = 2;

struct GameState {
  GameState(const Player &player1, const Player &player2, Ball ball)
    : players{player1, player2}, ball{std::move(ball)} {
  };
  std::array<Player, MAX_PLAYERS> players;
  Ball ball;
  Side lastGoal = Side::LEFT;

  [[nodiscard]] std::vector<const GameObject *> getObjects() const;

  void debugPrint();
};

#endif // GAMESTATE_H
