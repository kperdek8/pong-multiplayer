//
// Created by kperdek8 on 25.06.2024.
//

#include "GameObjects.h"
#include "GameField.h"

#include <iostream>

/* GameObject Class */

Direction GameObject::boundsCollision(const Vector2D &movement) const {
  Direction direction = Direction::NONE;
  if (position_.x + movement.x < 0)
    direction |= Direction::LEFT;
  else if (position_.x + width + movement.x > GameField::width)
    direction |= Direction::RIGHT;
  if (position_.y + movement.y < 0)
    direction |= Direction::BOTTOM;
  else if (position_.y + height + movement.y > GameField::height)
    direction |= Direction::TOP;
  return direction;
}

/*
  This function determines if two game objects collided. Collision requires
  objects to collide along both axes. When collision is detected this function
  determines collision axis.
*/

Direction GameObject::objectCollision(const GameObject &object,
                                      const Vector2D &movement) const {
  Direction direction = Direction::NONE;

  // Specific direction is distinguished based on movement (negative/positive).
  if (position_.x + movement.x <= object.position_.x + object.width &&
      position_.x + width + movement.x >= object.position_.x) {
    direction |= movement.x >= 0 ? Direction::RIGHT : Direction::LEFT;
  }
  if (position_.y + movement.y < object.position_.y + object.height &&
      position_.y + height + movement.y > object.position_.y) {
    direction |= movement.y >= 0 ? Direction::TOP : Direction::BOTTOM;
  }

  // Return none if there is only one axis overlap (objects don't collide)
  if (!(direction & (Direction::LEFT | Direction::RIGHT)) ||
      !(direction & (Direction::TOP | Direction::BOTTOM)))
    return Direction::NONE;

  // Check for overlap before movement
  const bool overlapXBefore =
      (position_.x < object.position_.x + object.width) &&
      (position_.x + width > object.position_.x);

  const bool overlapYBefore =
      (position_.y < object.position_.y + object.height) &&
      (position_.y + height > object.position_.y);

  if (!overlapXBefore && !overlapYBefore) {
    // Corner hit, return both axes direction
    return direction;
  }
  if (overlapXBefore && !overlapYBefore) {
    // X axis overlapped before movement, use Y axis direction
    return direction & (Direction::TOP | Direction::BOTTOM);
  }
  if (!overlapXBefore) {
    // Y axis overlapped before movement, use X axis direction
    return direction & (Direction::LEFT | Direction::RIGHT);
  }

  return direction;
}

/*
  This function calculates the distance from the current GameObject to another
  specified gamefield edge. The distance is measured from the edges of the
  current object.

  Using specific direction avoids edge case (when combined with boundsCollision)
  when object is closer to one side of game field, but makes movement big
  enough to collide with other side of field, which would result using distance
  to wrong edge.

  Using result from boundsCollision() also allows to use single movement offset
  when colliding with multiple edges in one frame without additional checks.
*/
Vector2D GameObject::distanceToBounds(const Direction direction) const {
  float minDistanceX = 0.0f;
  float minDistanceY = 0.0f;
  if (direction & Direction::LEFT)
    minDistanceX = 0.0f - position_.x;
  else if (direction & Direction::RIGHT)
    minDistanceX = GameField::width - (position_.x + width);
  if (direction & Direction::BOTTOM)
    minDistanceY = 0.0f - position_.y;
  else if (direction & Direction::TOP)
    minDistanceY = GameField::height - (position_.y + height);

  return Vector2D(minDistanceX, minDistanceY);
}

/*
  This function calculates the distance from the current GameObject to another
  GameObject. The distance is measured from the edges of the current object
  towards the edges of the other object.
*/
Vector2D GameObject::distanceToObject(const GameObject &object) const {
  float xDistance, yDistance;
  // Calculate distance along the X axis
  if (position_.x <= object.getX()) {
    // Object is to the right
    xDistance = object.getX() - (position_.x + width);
  } else {
    // Object is to the left
    xDistance = position_.x - (object.getX() + object.width);
  }
  // Calculate distance along the Y axis
  if (position_.y <= object.getY()) {
    // Object is above
    yDistance = object.getY() - (position_.y + height);
  } else {
    // Object is below
    yDistance = position_.y - (object.getY() + object.height);
  }

  return Vector2D(xDistance, yDistance);
}

void GameObject::move(const Vector2D &movement) {
  position_.x += movement.x;
  position_.y += movement.y;
}

/* Paddle Class */

void Paddle::resetPosition() { position_.y = GameField::height / 2.0f; }
void Paddle::addVelocity(const Vector2D &movement) {
  velocity_.y += velocity_.y + movement.y <= MOVESPEED
                     ? movement.y
                     : MOVESPEED - velocity_.y;
}
void Paddle::setVelocity(const Vector2D &movement) { velocity_.y = movement.y; }

/* Ball Class */

void Ball::bounce(const Direction direction) {
  if (direction & Direction::TOP || direction & Direction::BOTTOM) {
    velocity_.y = -velocity_.y;
  }
  if (direction & Direction::LEFT || direction & Direction::RIGHT) {
    velocity_.x = -velocity_.x;
  }
}
void Ball::start(const Side lastGoal) {
  const float angleDeviation = angleDist_(gen_);

  if (lastGoal == Side::LEFT) {
    velocity_.x = INITIAL_VELOCITY * std::cos(angleDeviation);
    velocity_.y = INITIAL_VELOCITY * std::sin(angleDeviation);
  } else {
    velocity_.x = -INITIAL_VELOCITY * std::cos(angleDeviation);
    velocity_.y = INITIAL_VELOCITY * std::sin(angleDeviation);
  }
}
void Ball::resetPosition() {
  velocity_ = Vector2D{0, 0};
  position_.x = GameField::width / 2.0f;
  position_.y = GameField::height / 2.0f;
}