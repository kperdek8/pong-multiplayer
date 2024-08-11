#include "Game.h"
#include "../common/ConnectionType.h"

int main() {
  //
  Game game(ConnectionType::HOST);
  while (game.isRunning()) {
  }
  return 0;
}
