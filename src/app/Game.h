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
#include "../controller/GameController.h"

class Game {
public:
  explicit Game(const ConnectionType &connectionType);

  ~Game();

  bool isRunning() const;

private:
  void initLocal();

  void initHost();

  void initClient();

  void initServer();

  void debug(Renderer &renderer) const;

  void gameLogic(GameController &gameController) const;

  void mainLoop();

  void stop();

  std::optional<Renderer> renderer_{};           // Optional to delay initialization
  std::optional<GameController> gameController_; // Optional to delay initialization
  std::optional<InputHandler> inputHandler_;     // Optional to delay initialization
  std::vector<std::thread> threads_;
  std::atomic<bool> running_ = false;
};


#endif //GAME_H
