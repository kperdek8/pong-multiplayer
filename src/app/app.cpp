#include <iostream>
#include "Game.h"
#include "../common/ConnectionType.h"

// TODO: Add unit tests for Input Handler

int main() {
  Game game(ConnectionType::LOCAL);
  while (game.isRunning()) {
  }
  return 0;
}
