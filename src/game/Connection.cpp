//
// Created by kperdek8 on 30.06.2024.
//

#include "Connection.h"
#include <format>
#include <iostream>

Connection::Connection(const std::function<void(Action, bool, int)> &callbackFunc,
                       const Player &player, const GameState &gameState)
  : callbackFunc_{callbackFunc}, player_{player}, gameState_{gameState} {
  std::cout << std::format("Connection {} created", this->getId()) << std::endl;
}

Connection::~Connection() {
  std::cout << "Connection object destroyed" << std::endl;
}

void Connection::sendAction(const Action action, const bool isActivated) const {
  callbackFunc_(action, isActivated, this->getId());
}

const GameState &Connection::getStateRef() const { return gameState_; }
