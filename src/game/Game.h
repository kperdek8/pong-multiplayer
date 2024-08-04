//
// Created by kperdek8 on 04.08.2024.
//

#ifndef GAME_H
#define GAME_H
#include <thread>
#include <vector>

#include "../common/ConnectionType.h"
#include "../input/InputHandler.h"
#include "../renderer/Renderer.h"
#include "GameController.h"

class Game {
public:
  explicit Game(ConnectionType connectionType);
  ~Game();
  bool isRunning() const;
private:
  void debug(Renderer &renderer) const;
  void gameLogic(GameController &gameController) const;
  void mainLoop();
  void stop();
  Renderer renderer_ {};
  GameController gameController_;
  std::optional<InputHandler> inputHandler_;  // Optional to delay initialization
  std::vector<std::thread> threads_;
  std::atomic<bool> running_ = false;
};



#endif //GAME_H
