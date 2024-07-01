//
// Created by kperdek8 on 25.06.2024.
//

#include "GameController.h"

#include <algorithm>
#include <format>
#include <iostream>

std::optional<std::weak_ptr<Connection>> GameController::attach() {
  // Check if there is empty connection slot
  const auto it = std::ranges::find_if(
      connections_, [](const auto &conn) { return conn == nullptr; });

  // Reject connection if all slots are taken
  if (it == connections_.end()) {
    std::cout << "New connection rejected" << std::endl;
    return std::nullopt;
  }

  // Bind the processAction member function to this instance
  auto callback = [this](const Action action, const int id) {
    this->processAction(action, id);
  };

  // Pass assigned player as reference
  const auto playerId = std::distance(connections_.begin(), it);
  Player &player = gameState_.players[playerId];

  *it = std::make_shared<Connection>(callback, player, gameState_);
  return std::weak_ptr(*it);
}

void GameController::detach(const std::weak_ptr<Connection> &connection) {
  if (const auto shared_conn = connection.lock()) {
    auto it = std::ranges::find_if(connections_, [&](const auto &conn) {
      return conn && conn->getId() == shared_conn->getId();
    });

    if (it != connections_.end()) {
      it->reset();
      std::cout << std::format("Connection {} detached", shared_conn->getId())
                << std::endl;
    }
  }
}

void GameController::processAction(const Action action, int id) {
  std::cout << std::format("Connection {}: ", id);
  constexpr auto speed = Paddle::MOVESPEED;
  switch (action) {
  case Action::NONE:
    std::cout << "No Actions!" << std::endl;
  case Action::MOVE_UP:
    std::cout << "Move up!" << std::endl;
    gameState_.players[id].paddle.addVelocity(Vector2D{0, speed});
    break;
  case Action::MOVE_DOWN:
    std::cout << "Move down!" << std::endl;
    gameState_.players[id].paddle.addVelocity(Vector2D{0, -speed});
    break;
  case Action::PAUSE:
    std::cout << "Pause" << std::endl;
    break;
  case Action::START:
    std::cout << "Start" << std::endl;
    break;
  }
}

std::size_t GameController::getConnectionCount() {
  const auto connections = std::ranges::count_if(
      connections_, [](const auto &conn) { return conn != nullptr; });
  return connections;
}

bool GameController::isConnectionAvailable() {
  const auto it = std::ranges::find_if(
      connections_, [](const auto &conn) { return conn == nullptr; });
  return it != connections_.end();
}

inline void handleBoundsCollision(GameObject &object, Vector2D &movement) {
  if (const auto direction = object.boundsCollision(movement)) {
    const auto distance = object.distanceToBounds(direction);
    if (direction & Direction::TOP)
      movement.y = std::min(movement.y, distance.y);
    else if (direction & Direction::BOTTOM)
      movement.y = std::max(movement.y, distance.y);
    if (direction & Direction::RIGHT)
      movement.x = std::min(movement.x, distance.x);
    else if (direction & Direction::LEFT)
      movement.x = std::max(movement.x, distance.x);

    if (auto *ball = dynamic_cast<Ball *>(&object)) {
      ball->bounce(direction); // Call bounce if `object` is a `Ball`
    }
  }
}

inline void handleObjectCollision(GameObject &object, Vector2D &movement,
                                  const GameObject &otherObject) {
  if (const auto direction = object.objectCollision(otherObject, movement)) {
    auto distance = object.distanceToObject(otherObject);
    if (direction & Direction::TOP)
      movement.y = std::min(movement.y, distance.y);
    else if (direction & Direction::BOTTOM)
      movement.y = std::max(movement.y, distance.y);
    if (direction & Direction::RIGHT)
      movement.x = std::min(movement.x, distance.x);
    else if (direction & Direction::LEFT)
      movement.x = std::max(movement.x, distance.x);

    if (auto *ball = dynamic_cast<Ball *>(&object)) {
      ball->bounce(direction); // Call bounce if `object` is a `Ball`
    }
  }
}

void GameController::update() {
  // Delta time calculation
  const auto currentFrame = std::chrono::high_resolution_clock::now();
  const std::chrono::duration<float> deltaTime = currentFrame - lastFrame_;
  const float dt = deltaTime.count();
  lastFrame_ = currentFrame;

  // Paddles
  for (auto &player : gameState_.players) {
    auto movement = player.paddle.getVel() * dt;
    handleBoundsCollision(player.paddle, movement);
    player.paddle.move(movement);
  }

  // Ball
  auto movement = gameState_.ball.getVel() * dt;

  for (auto &player : gameState_.players) {
    handleObjectCollision(gameState_.ball, movement, player.paddle);
  }

  if (const auto direction = gameState_.ball.boundsCollision(movement)) {
    handleBoundsCollision(gameState_.ball, movement);
  }
  gameState_.ball.move(movement);

  // Other stuff
  gameState_.debugPrint();
}
void GameController::start() {
  gameStarted_ = true;
  lastFrame_ = std::chrono::high_resolution_clock::now();
  gameState_.ball.start(gameState_.lastGoal);
}
