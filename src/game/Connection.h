//
// Created by kperdek8 on 30.06.2024.
//

#ifndef CONNECTION_H
#define CONNECTION_H

#include "Action.h"
#include "GameObjects.h"
#include "GameState.h"
#include <functional>

class Connection {
public:
  explicit Connection(const std::function<void(Action, bool, int)> &callbackFunc,
                      const Player &player, const GameState &gameState);

  ~Connection();

  void sendAction(Action action, bool isActivated) const;

  [[nodiscard]] constexpr int getId() const { return player_.id; }

  [[nodiscard]] const GameState &getStateRef() const;

private:
  std::function<void(Action, bool, int)> callbackFunc_;
  /* Make player data and gamestate read-only outside of GameController class */
  /* It probably should be replaced with second callbackFunc
    (GameControler->Client communication) sending updates about game state to
    keep behaviour the same with communication over internet. */
  const Player &player_;
  const GameState &gameState_;
};

#endif // CONNECTION_H
