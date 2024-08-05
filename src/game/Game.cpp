//
// Created by kperdek8 on 04.08.2024.
//


#include <iostream>
#include "Game.h"
#include <cassert>
#include "GameController.h"

void Game::initLocal() {
  gameController_.emplace(ConnectionType::LOCAL);
  // Attach the two local connections
  std::optional<std::weak_ptr<Connection>> optConnection1 = gameController_->attachLocally();
  assert(optConnection1 && "Attaching connection1 during Local game initialization should not fail!");

  std::optional<std::weak_ptr<Connection> > optConnection2 = gameController_->attachLocally();
  assert(optConnection2 && "Attaching connection2 during Local game initialization should not fail!");

  // Lock connections
  std::shared_ptr<Connection> connection1 = optConnection1->lock();
  assert(connection1 && "Locking connection1 during Local game initialization should not fail!");

  std::shared_ptr<Connection> connection2 = optConnection2->lock();
  assert(connection1 && "Locking connection2 during Local game initialization should not fail!");

  renderer_.emplace();
  inputHandler_.emplace(InputHandler{ConnectionType::LOCAL});
  inputHandler_->attachToRenderer(&(*renderer_));
  inputHandler_->attachConnection(connection1, 0);
  inputHandler_->attachConnection(connection2, 1);

  running_.store(true);
  threads_.emplace_back(&Game::gameLogic, this, std::ref(*gameController_));
  threads_.emplace_back(&Game::debug, this, std::ref(*renderer_));
  mainLoop();
}

void Game::initHost() {
  // Attach first connection
  std::optional<std::weak_ptr<Connection>> optConnection1 = gameController_->attachLocally();
  assert(optConnection1 && "Attaching connection1 during Local game initialization should not fail!");
  // Lock connection
  std::shared_ptr<Connection> connection1 = optConnection1->lock();
  assert(connection1 && "Locking connection1 during Local game initialization should not fail!");
}

void Game::initClient() {
  // Implement
}

void Game::initServer() {
  // Implement
}

Game::Game(const ConnectionType& connectionType) {
  switch(connectionType) {
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
  for(auto& thread : threads_) {
    if(thread.joinable())
      thread.join();
  }
}

void Game::gameLogic(GameController &gameController) const {
  gameController.start();
  while (running_.load() == true) {
    gameController.update();
  }
}


void Game::debug(Renderer &renderer) const {
  int lastFps = -1;
  while (running_.load() == true) {
    int fps = renderer.GetFPS();
    if (fps != lastFps) {
      std::cout << "FPS: " << fps << std::endl;
      lastFps = fps;
    }
  }
}


void Game::mainLoop() {
  GameState &gameState = gameController_->getGameState();

  while (running_.load()) {
    renderer_->Update(gameState.getObjects());
    inputHandler_->handleInput();
    if (inputHandler_->isActionTriggered(Action::QUIT)) {
      running_.store(false);
    }
  }
  stop();
}

bool Game::isRunning() const{
  return running_.load();
}

void Game::stop() {
  running_.store(false);
}