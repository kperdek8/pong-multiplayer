//
// Created by kperdek8 on 30.06.2024.
//

#ifndef DIRECTION_H
#define DIRECTION_H

enum Direction : unsigned char {
  TOP = 0b0001,
  LEFT = 0b0010,
  BOTTOM = 0b0100,
  RIGHT = 0b1000,
  NONE = 0b0000
};

inline Direction operator|(const Direction lhs, const Direction rhs) {
  return static_cast<Direction>(static_cast<unsigned char>(lhs) |
                                static_cast<unsigned char>(rhs));
}

inline Direction &operator|=(Direction &lhs, const Direction rhs) {
  lhs = lhs | rhs;
  return lhs;
}

inline bool operator&(const Direction lhs, const Direction rhs) {
  return static_cast<bool>(static_cast<unsigned char>(lhs) &
                           static_cast<unsigned char>(rhs));
}

#endif // DIRECTION_H
