//
// Created by kperdek8 on 25.06.2024.
//

#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <optional>
#include <array>
#include <functional>
#include <memory>

#include "GameObjects.h"

enum class Action {
  MOVE_UP,
  MOVE_DOWN,
  PAUSE
};

class Connection {
public:
  explicit Connection(int id, const std::function<void(Action, int)>& callbackFunc);
  ~Connection();
  void sendAction(Action action) const;
  [[nodiscard]] constexpr int getId() const { return player_.id;}
private:
  std::function<void(Action, int)> callbackFunc_;
  Player player_;
};

constexpr std::size_t MAX_PLAYERS = 2;

class GameController {
public:
  GameController();
  std::optional<std::weak_ptr<Connection>> attach();
  void detach(const std::weak_ptr<Connection>& connection);
  std::size_t getConnectionCount();
  bool isConnectionAvailable();
private:
  void processAction(Action action, int id);
  std::array<std::shared_ptr<Connection>, MAX_PLAYERS> connections_ {};
};

#endif //GAMECONTROLLER_H
