//
// Created by kperdek8 on 25.06.2024.
//

#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <array>
#include <functional>
#include <memory>
#include <optional>

#include "GameObjects.h"
#include "Action.h"
#include "Connection.h"
#include "GameState.h"

class GameController {
public:
  GameController() : gameState_{Player{0}, Player{1}, Ball{}} {};
  std::optional<std::weak_ptr<Connection>> attach();
  void detach(const std::weak_ptr<Connection> &connection);
  std::size_t getConnectionCount();
  bool isConnectionAvailable();
  void update();

private:
  GameState gameState_;
  const GameField gameField_{};
  bool gameStarted = false;
  std::array<std::shared_ptr<Connection>, MAX_PLAYERS> connections_{};

  void processAction(Action action, int id);
};

#endif // GAMECONTROLLER_H
