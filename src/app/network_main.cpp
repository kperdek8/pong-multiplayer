//
// Created by kperdek8 on 27.07.2024.
//

#include <iostream>

#include "SDL3/SDL.h"
#include "NetworkServer.h"

void networkThread(std::vector<std::shared_ptr<Connection>>& connections) {
  NetworkServer server(4444);
  server.Listen(connections);
}

int main() {
  SDL_Init(SDL_INIT_VIDEO);
  try {
    std::vector<std::shared_ptr<Connection>> connections;
    std::thread thread(networkThread,std::ref(connections));
    while(connections.empty()) {

    }
    Data data = std::string("11110000");
    connections.back()->send(data);

    while(true) {

    }
    thread.join();
  }
  catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}