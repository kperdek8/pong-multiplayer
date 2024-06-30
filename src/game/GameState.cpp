//
// Created by kperdek8 on 30.06.2024.
//

#include "GameState.h"
#include <format>
#include <iostream>

void GameState::debugPrint() {
  std::cout << std::format("Last goal by {}",
                           (this->lastGoal == Side::LEFT ? "left" : "right"))
            << std::endl;
  std::cout << std::format("Score {} : {}", this->players[0].points,
                           this->players[1].points)
            << std::endl;
  std::cout << std::format("Paddle {} position (x: {} y: {})",
                           this->players[0].id, this->players[0].paddle.getX(),
                           this->players[0].paddle.getY())
            << std::endl;
  std::cout << std::format("Paddle {} position (x: {} y: {})",
                           this->players[1].id, this->players[1].paddle.getX(),
                           this->players[1].paddle.getY())
            << std::endl;
}