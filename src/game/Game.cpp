//
// Created by kperdek8 on 04.08.2024.
//


#include <iostream>
#include "Game.h"
#include "GameController.h"

Game::Game(ConnectionType connectionType) : gameController_(connectionType) {
  // Attach the first connection
  std::optional<std::weak_ptr<Connection> > optConnection1 = gameController_.attachLocally();
  if (!optConnection1) {
    std::cerr << "Failed to attach first connection" << std::endl;
    exit(1);
  }

  // Attach the second connection
  std::optional<std::weak_ptr<Connection> > optConnection2 = gameController_.attachLocally();
  if (!optConnection2) {
    std::cerr << "Failed to attach second connection" << std::endl;
    exit(1);
  }

  // Lock the first connection
  std::shared_ptr<Connection> connection1 = optConnection1->lock();
  if (!connection1) {
    std::cerr << "Failed to lock first connection" << std::endl;
    exit(1);
  }

  // Lock the second connection
  std::shared_ptr<Connection> connection2 = optConnection2->lock();
  if (!connection2) {
    std::cerr << "Failed to lock second connection" << std::endl;
    exit(1);
  }

  inputHandler_.emplace(InputHandler{connectionType,connection1, connection2});
  inputHandler_->attach(&renderer_);

  running_.store(true);
  threads_.emplace_back(&Game::gameLogic, this, std::ref(gameController_));
  threads_.emplace_back(&Game::debug, this, std::ref(renderer_));
  mainLoop();
}

Game::~Game() {
  stop();
  for(auto& thread : threads_) {
    std::cout<<"C"<<std::endl;
    if(thread.joinable())
      thread.join();
  }
  std::cout<<"D"<<std::endl;
}

void Game::gameLogic(GameController &gameController) const {
  gameController.start();
  while (running_.load() == true) {
    gameController.update();
  }
  std::cout<<"A"<<std::endl;
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
  std::cout<<"B"<<std::endl;
}


void Game::mainLoop() {
  GameState &gameState = gameController_.getGameState();

  while (running_.load()) {
    renderer_.Update(gameState.getObjects());
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