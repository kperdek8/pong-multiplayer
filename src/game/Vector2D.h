//
// Created by kperdek8 on 01.07.2024.
//

#ifndef VECTOR2D_H
#define VECTOR2D_H

struct Vector2D {
  float x;
  float y;

  explicit Vector2D(const float x = 0.0f, const float y = 0.0f) : x(x), y(y) {}

  Vector2D operator+(const Vector2D &other) const {
    return Vector2D(x + other.x, y + other.y);
  }

  Vector2D &operator+=(const Vector2D &other) {
    x += other.x;
    y += other.y;
    return *this;
  }

  Vector2D operator-(const Vector2D &other) const {
    return Vector2D(x - other.x, y - other.y);
  }

  Vector2D &operator-=(const Vector2D &other) {
    x -= other.x;
    y -= other.y;
    return *this;
  }

  Vector2D operator*(const float scalar) const {
    return Vector2D(x * scalar, y * scalar);
  }

  Vector2D& operator*=(const float scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
  }

  bool operator==(const Vector2D &other) const {
    return x == other.x && y == other.y;
  }
};

#endif // VECTOR2D_H
