//
// Created by kperdek8 on 27.07.2024.
//

#ifndef DATA_H
#define DATA_H

#include "../game/GameState.h"
#include "../game/Action.h"
#include <bitset>

class Data {
public:
  Data(Action &action, bool pressed) {
    data_ = std::bitset<8>(0b11001100); // testing
  }

  Data(GameState &gameState) {
    data_ = std::bitset<8>(0b11001100); // testing
  }

  Data(const std::string &data) {
    data_ = std::bitset<8>(data); // testing
  }

  [[nodiscard]] std::string read() const {
    return data_.to_string();
  }

private:
  std::bitset<8> data_;
};

#endif //DATA_H
