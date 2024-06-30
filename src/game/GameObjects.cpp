//
// Created by kperdek8 on 25.06.2024.
//

#include "GameObjects.h"

/* GameObject Class */

/* Direction is represented as bitmask to easily return horizontal and vertical
   collision as the same time.
 */
Direction GameObject::boundsCollision(const float xMovement,
                                      const float yMovement) const {
  Direction direction = Direction::NONE;
  if (x_ - xMovement < 0)
    direction |= Direction::LEFT;
  else if (x_ + width + xMovement > GameField::width)
    direction |= Direction::RIGHT;
  if (y_ - yMovement < 0)
    direction |= Direction::BOTTOM;
  else if (y_ + height + yMovement > GameField::height)
    direction |= Direction::TOP;
  return direction;
}

/* Direction is represented as bitmask to easily return horizontal and vertical
 * collision as the same time.
 */
bool GameObject::objectCollision(const GameObject &object,
                                 const float xMovement,
                                 const float yMovement) const {
  Direction direction = Direction::NONE;
  if (x_ - xMovement < object.x_ + object.width)
    direction |= Direction::LEFT;
  else if (x_ + width + xMovement > object.x_)
    direction |= Direction::RIGHT;
  if (y_ - yMovement < object.y_ + object.height)
    direction |= Direction::BOTTOM;
  else if (y_ + height + yMovement > object.y_)
    direction |= Direction::TOP;

  return direction;
}
void GameObject::update(const float dt) {
  x_ += xVelocity_ * dt;
  y_ += yVelocity_ * dt;
}

/* Paddle Class */

void Paddle::resetPosition() { y_ = GameField::height / 2.0f; }
void Paddle::addVelocity(const float yVel) {
  yVelocity_ +=
      yVelocity_ + yVel <= MAX_VELOCITY ? yVel : MAX_VELOCITY - yVelocity_;
}

/* Ball Class */

void Ball::bounce(const Direction direction) {
  if (direction & Direction::TOP || direction & Direction::BOTTOM) {
    yVelocity_ = -yVelocity_;
  }
  if (direction & Direction::LEFT || direction & Direction::RIGHT) {
    xVelocity_ = -xVelocity_;
  }
}
void Ball::start(const Side lastGoal) {
  const float angleDeviation = angleDist_(gen_);

  if (lastGoal == Side::LEFT) {
    xVelocity_ = INITIAL_VELOCITY * std::cos(angleDeviation);
    yVelocity_ = INITIAL_VELOCITY * std::sin(angleDeviation);
  } else {
    xVelocity_ = -INITIAL_VELOCITY * std::cos(angleDeviation);
    yVelocity_ = INITIAL_VELOCITY * std::sin(angleDeviation);
  }
}
void Ball::resetPosition() {
  x_ = GameField::width / 2.0f;
  y_ = GameField::height / 2.0f;
}