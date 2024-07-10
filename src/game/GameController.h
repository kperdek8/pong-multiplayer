//
// Created by kperdek8 on 25.06.2024.
//

#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <array>
#include <chrono>
#include <functional>
#include <memory>
#include <optional>

#include "Action.h"
#include "Connection.h"
#include "GameField.h"
#include "GameObjects.h"
#include "GameState.h"

class GameController {
public:
  GameController()
    : gameState_{Player{0}, Player{1}, Ball{GameField::width / 2.0f, GameField::height / 2.0f}} {
  }

  std::optional<std::weak_ptr<Connection> > attach();

  void detach(const std::weak_ptr<Connection> &connection);

  std::size_t getConnectionCount();

  bool isConnectionAvailable();

  // Make these private later and manipulate gameloop only via connection.
  void update();

  void start();

private:
  GameState gameState_;
  const GameField gameField_{};
  bool gameStarted_ = false;
  std::chrono::time_point<std::chrono::high_resolution_clock> lastFrame_;

  std::array<std::shared_ptr<Connection>, MAX_PLAYERS> connections_{};

  void handleBoundsCollision(GameObject &object, Vector2D &movement);

  void handleObjectCollision(GameObject &object, Vector2D &movement,
                             const GameObject &otherObject);

  void processAction(Action action, int id);
};

#endif // GAMECONTROLLER_H
