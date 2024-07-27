//
// Created by kperdek8 on 30.06.2024.
//

#ifndef ACTION_H
#define ACTION_H

#include <ostream>

enum class Action {
  NONE = 0b0000, MOVE_UP = 0b0001, MOVE_DOWN = 0b0010, PAUSE = 0b0011, START = 0b0100, QUIT = 0b0101
};

inline std::ostream &operator <<(std::ostream &os, const Action &obj) {
  os << static_cast<std::underlying_type_t<Action>>(obj);
  return os;
}

#endif //ACTION_H
