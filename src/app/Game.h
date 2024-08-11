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

  void debug() const;

  void gameLogic();

  void networking();

  void mainLoop();

  void stop();

  ConnectionType type_;
  std::optional<Renderer> renderer_{};           // Optional to allow delayed initialization
  std::optional<GameController> gameController_; // Optional to allow delayed initialization
  std::optional<InputHandler> inputHandler_;     // Optional to allow delayed initialization
  NetworkManager* networkManager_ = nullptr;               // Not always exposed to Game
  std::vector<std::thread> threads_;
  std::atomic<bool> running_ = false;
};


#endif //GAME_H
