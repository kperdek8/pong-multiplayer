#include "GameController.h"
#include "Renderer.h"
#include <iostream>

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
  // connection1->sendAction(Action::MOVE_UP);
  controller.start();
  while (true) {
    controller.update();
    renderer.update(gameState.getObjects());
  }

  return 0;
}
