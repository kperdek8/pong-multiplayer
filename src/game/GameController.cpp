//
// Created by kperdek8 on 25.06.2024.
//

#include "GameController.h"

#include <algorithm>
#include <format>
#include <iostream>
#include <memory>

/* Connection Class */

Connection::Connection(const std::function<void(Action, int)> &callbackFunc,
                       const Player &player, const GameState &gameState)
    : callbackFunc_{callbackFunc}, player_{player}, gameState_{gameState} {
  std::cout << std::format("Connection {} created", this->getId()) << std::endl;
}

Connection::~Connection() {
  std::cout << "Connection object destroyed" << std::endl;
}

void Connection::sendAction(const Action action) const {
  callbackFunc_(action, this->getId());
}

/* GameState Struct */

void GameState::debugPrint() {
  std::cout << std::format("Last goal by {}",
                           (this->lastGoal == Side::LEFT ? "left" : "right"))
            << std::endl;
  std::cout << std::format("Score {} : {}", this->players[0].points,
                           this->players[1].points)
            << std::endl;
  std::cout << std::format("Paddle {} position (x: {} y: {})",
                           this->players[0].id, this->players[0].paddle.x,
                           this->players[0].paddle.y)
            << std::endl;
  std::cout << std::format("Paddle {} position (x: {} y: {})",
                           this->players[1].id, this->players[1].paddle.x,
                           this->players[1].paddle.y)
            << std::endl;
}

/* GameController Class */

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

void GameController::processAction(Action action, int id) {
  std::cout << std::format("Connection {}: ", id);
  switch (action) {
  case Action::NONE:
    std::cout << "No Actions!" << std::endl;
  case Action::MOVE_UP:
    std::cout << "Move up!" << std::endl;
    gameState_.players[id].paddle.y += 1;
    break;
  case Action::MOVE_DOWN:
    std::cout << "Move down!" << std::endl;
    gameState_.players[id].paddle.y -= 1;
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

void GameController::update() { gameState_.debugPrint(); }
