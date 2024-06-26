//
// Created by kperdek8 on 25.06.2024.
//

#include "GameController.h"

#include <algorithm>
#include <format>
#include <iostream>
#include <memory>

/* Connection Class */

Connection::Connection(const int id, const std::function<void(Action, int)>& callbackFunc) : callbackFunc_{callbackFunc}, player_{id} {
  std::cout<<std::format("Connection {} created", id)<<std::endl;
}

Connection::~Connection() {
  std::cout<<"Connection object destroyed"<<std::endl;
}

void Connection::sendAction(const Action action) const {
  callbackFunc_(action, this->getId());
}

/* GameController Class */

GameController::GameController() = default;

std::optional<std::weak_ptr<Connection>> GameController::attach() {
  const auto it = std::ranges::find_if(connections_, [](const auto& conn) {
    return conn == nullptr;
  });
  // Check if there is empty connection slot
  if(it == connections_.end()) {
    std::cout << "New connection rejected" << std::endl;
    return std::nullopt;
  }

  // Bind the processAction member function to this instance
  auto callback = [this](Action action, int id) {
    this->processAction(action, id);
  };

  *it = std::make_shared<Connection>(std::distance(connections_.begin(), it), callback);
  return std::weak_ptr(*it);
}

void GameController::detach(const std::weak_ptr<Connection>& connection) {
  if (const auto shared_conn = connection.lock()) {
    auto it = std::ranges::find_if(connections_, [&](const auto& conn) {
      return conn && conn->getId() == shared_conn->getId();
    });

    if (it != connections_.end()) {
      it->reset();
      std::cout << std::format("Connection {} detached", shared_conn->getId()) << std::endl;
    }
  }
}

void GameController::processAction(Action action, int id) {
  switch(action) {
    case Action::MOVE_UP:
      std::cout<<"Move up!"<<std::endl;
      break;
    case Action::MOVE_DOWN:
      std::cout<<"Move down!"<<std::endl;
      break;
    case Action::PAUSE:
      std::cout<<"Pause"<<std::endl;
      break;
  }
}

std::size_t GameController::getConnectionCount() {
  const auto connections = std::ranges::count_if(connections_, [](const auto& conn) {
    return conn != nullptr;
  });
  return connections;
}

bool GameController::isConnectionAvailable() {
  const auto it = std::ranges::find_if(connections_, [](const auto& conn) {
    return conn == nullptr;
  });
  return it != connections_.end();
}
