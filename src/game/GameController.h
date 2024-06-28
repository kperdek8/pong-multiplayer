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

constexpr std::size_t MAX_PLAYERS = 2;

struct GameState {
  GameState(const Player &player1, const Player &player2, const Ball &ball)
      : players{player1, player2}, ball{ball} {};
  std::array<Player, MAX_PLAYERS> players;
  Ball ball;
  Side lastGoal = LEFT;

  void debugPrint();
};

enum class Action { NONE, MOVE_UP, MOVE_DOWN, PAUSE, START };

class Connection {
public:
  explicit Connection(const std::function<void(Action, int)> &callbackFunc,
                      const Player &player, const GameState &gameState);
  ~Connection();
  void sendAction(Action action) const;
  [[nodiscard]] constexpr int getId() const { return player_.id; }

private:
  std::function<void(Action, int)> callbackFunc_;
  /* Make player data and gamestate read-only outside of GameController class */
  /* It probably should be replaced with second callbackFunc
    (GameControler->Client communication) sending updates about game state to
    keep behaviour the same with communication over internet. */
  const Player &player_;
  const GameState &gameState_;
};

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
