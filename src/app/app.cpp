#include "GameController.h"
#include "Renderer.h"
#include <iostream>

#include "InputHandler.h"
#include "KeyMapping.h"
#include "Action.h"
#include "SDL3/SDL_keycode.h"

const KeyMapping player1_keys = {
  std::pair(SDLK_W, Action::MOVE_UP),
  std::pair(SDLK_S, Action::MOVE_DOWN),
  std::pair(SDLK_P, Action::PAUSE),
  std::pair(SDLK_ESCAPE, Action::QUIT),
  std::pair(SDLK_SPACE, Action::START)
};
const KeyMapping player2_keys = {
  std::pair(SDLK_UP, Action::MOVE_UP),
  std::pair(SDLK_DOWN, Action::MOVE_DOWN),
  std::pair(SDLK_P, Action::PAUSE),
  std::pair(SDLK_ESCAPE, Action::QUIT),
  std::pair(SDLK_SPACE, Action::START)
};


// TODO: Add unit tests for Input Handler

int main() {
  GameController controller;
  Renderer renderer;

  // Attach the first connection
  std::optional<std::weak_ptr<Connection> > optConnection1 = controller.attach();
  if (!optConnection1) {
    std::cerr << "Failed to attach first connection" << std::endl;
    return 1;
  }

  // Attach the second connection
  std::optional<std::weak_ptr<Connection> > optConnection2 = controller.attach();
  if (!optConnection2) {
    std::cerr << "Failed to attach second connection" << std::endl;
    return 1;
  }

  // Lock the first connection
  std::shared_ptr<Connection> connection1 = optConnection1->lock();
  if (!connection1) {
    std::cerr << "Failed to lock first connection" << std::endl;
    return 1;
  }

  // Lock the second connection
  std::shared_ptr<Connection> connection2 = optConnection2->lock();
  if (!connection2) {
    std::cerr << "Failed to lock second connection" << std::endl;
    return 1;
  }
  const GameState &gameState = connection1->getStateRef();

  InputHandler inputHandler{connection1, connection2, player1_keys, player2_keys};

  controller.start();
  bool running = true;
  while (running) {
    controller.update();
    renderer.update(gameState.getObjects());
    inputHandler.handleInput();
    if (inputHandler.isActionTriggered(Action::QUIT)) {
      running = false;
    }
  }

  return 0;
}
