//
// Created by kperdek8 on 27.07.2024.
//

#ifndef DATA_H
#define DATA_H

#include <bitset>
#include "Action.h"
#include "../game/GameState.h"
#include "Action.h"

class Data {
public:
  Data(const Action action, const bool pressed) {
    //data_ = std::bitset<8>(0b11001100); // testing
    action_ = action;
    pressed_ = pressed;
  }

  Data(GameState* gameState) : gameState_(gameState){
    //data_ = std::bitset<8>(0b11001100); // testing
  }

  Data(const std::string &data) {
    data_ = std::bitset<8>(data); // testing
  }

  [[nodiscard]] std::string read() const {
    return data_.to_string();
  }

  [[nodiscard]] std::pair<Action, bool> readAction() const {
    return {action_, pressed_}; // testing
  }

private:
  std::bitset<8> data_;
  // For testing, before I implement bit data dictionary
  GameState* gameState_{};
  Action action_{};
  bool pressed_{};
};

#endif //DATA_H
