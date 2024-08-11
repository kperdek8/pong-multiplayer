//
// Created by kperdek8 on 25.06.2024.
//

#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <chrono>
#include <memory>
#include <optional>

#include "../common/Action.h"
#include "../networking/Connection.h"
#include "../networking/NetworkManager.h"
#include "GameField.h"
#include "GameObjects.h"
#include "GameState.h"

class GameController {
public:
  // TODO: Replace passed stateFetchFunc as new function which will encode GameState as Data object
  explicit GameController()
    : gameState_{Player{0}, Player{1}, Ball{GameField::width / 2.0f, GameField::height / 2.0f}},
  networkManager_{[this]() { return Data(std::string{"01010101"});}} {}

  ~GameController() {
    networkManager_.stop();
  }

  std::optional<std::weak_ptr<Connection> > attachLocally();

  GameState &getGameState();

  /* For multiplayer game it's necessary to access NetworkManager from outside, because neither GameController nor
   * NetworkManager have knowledge about type of game.
   */
  NetworkManager* getNetworkManager();

  void update();
  void stop();
  void start();

private:
  GameState gameState_;
  NetworkManager networkManager_;
  const GameField gameField_{};
  bool gameStarted_ = false;
  std::chrono::time_point<std::chrono::high_resolution_clock> lastFrame_;

  void handleBoundsCollision(GameObject &object, Vector2D &movement);

  void handleObjectCollision(GameObject &object, Vector2D &movement,
                             const GameObject &otherObject);

  void processAction(Action action, bool isActivated, int id);
};

#endif // GAMECONTROLLER_H
