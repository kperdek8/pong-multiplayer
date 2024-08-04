#include <iostream>
#include "Game.h"
#include "../common/ConnectionType.h"

// TODO: Add unit tests for Input Handler
// TODO: Separate creating Connections to controller based on connection type
// TODO: Think of better way to pass Connections to InputHandler

int main() {
  Game game(ConnectionType::LOCAL);
  while(game.isRunning()) {

  }
  return 0;
}
