//
// Created by kperdek8 on 04.08.2024.
//


#include <iostream>
#include <cassert>
#include "Game.h"
#include "../controller/GameController.h"

void Game::initLocal() {
  gameController_.emplace();
  // Attach the two local connections
  std::optional<std::weak_ptr<Connection> > optConnection1 = gameController_->attachLocally();
  assert(optConnection1 && "Attaching connection1 during Local game initialization should not fail!");

  std::optional<std::weak_ptr<Connection> > optConnection2 = gameController_->attachLocally();
  assert(optConnection2 && "Attaching connection2 during Local game initialization should not fail!");

  // Lock connections
  std::shared_ptr<Connection> connection1 = optConnection1->lock();
  assert(connection1 && "Locking connection1 during Local game initialization should not fail!");

  std::shared_ptr<Connection> connection2 = optConnection2->lock();
  assert(connection1 && "Locking connection2 during Local game initialization should not fail!");

  // Initialize required modules
  renderer_.emplace();
  inputHandler_.emplace(InputHandler{ConnectionType::LOCAL});
  inputHandler_->attachToRenderer(&(*renderer_));
  inputHandler_->attachConnection(connection1, 0);
  inputHandler_->attachConnection(connection2, 1);

  // Start threads
  running_.store(true);
  threads_.emplace_back(&Game::gameLogic, this);
  threads_.emplace_back(&Game::debug, this);
  mainLoop();
}

void Game::initHost() {
  // Attach first connection
  gameController_.emplace();
  networkManager_ = gameController_->getNetworkManager();
  std::optional<std::weak_ptr<Connection> > optConnection1 = gameController_->attachLocally();
  assert(optConnection1 && "Attaching host connection during initialization should not fail!");
  // Lock connection
  std::shared_ptr<Connection> connection1 = optConnection1->lock();
  assert(connection1 && "Locking host connection during initialization should not fail!");

  // Initialize required modules
  renderer_.emplace();
  inputHandler_.emplace(InputHandler{ConnectionType::HOST});
  inputHandler_->attachToRenderer(&(*renderer_));
  inputHandler_->attachConnection(connection1, 0);

  // Start threads
  running_.store(true);
  threads_.emplace_back(&Game::gameLogic, this);
  threads_.emplace_back(&Game::debug, this);
  threads_.emplace_back(&Game::networking, this);
  mainLoop();
}

void Game::initClient() {
  // Implement
}

void Game::initServer() {
  // Implement
}

Game::Game(const ConnectionType &connectionType) : type_(connectionType) {
  switch (connectionType) {
    case ConnectionType::LOCAL:
      initLocal();
      break;
    case ConnectionType::HOST:
      initHost();
      break;
    case ConnectionType::CLIENT:
      initClient();
      break;
    case ConnectionType::SERVER:
      initServer();
      break;
  }
}

Game::~Game() {
  stop();
}

void Game::gameLogic() {
  while (running_.load()) {
    gameController_->update();
  }
  gameController_->stop();
}

void Game::networking() {
  assert(networkManager_ != nullptr && "Networking thread should get created without initialized NetworkManager");
  if(!networkManager_)
      return;
  while(running_.load()) {
    if(networkManager_->isConnectionAvailable() >= 0)
      networkManager_->getNewConnection(4445);
  }
}

void Game::debug() const {
  int lastFps = -1;
  while (running_.load()) {
    int fps = renderer_->GetFPS();
    if (fps != lastFps) {
      std::cout << "FPS: " << fps << std::endl;
      lastFps = fps;
    }
  }
}


void Game::mainLoop() {
  const GameState &gameState = gameController_->getGameState();

  while (running_.load()) {
    renderer_->Update(gameState);
    inputHandler_->handleInput();
    if (inputHandler_->isActionTriggered(Action::QUIT)) {
      running_.store(false);
    }
  }
}

bool Game::isRunning() const {
  return running_.load();
}

void Game::stop() {
  running_.store(false);
  for (auto &thread: threads_) {
    if (thread.joinable())
      thread.join();
  }
}
