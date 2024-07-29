//
// Created by kperdek8 on 27.07.2024.
//

#include <iostream>

#include "SDL3/SDL.h"
#include "NetworkClient.h"

void networkThread(std::shared_ptr<Connection>& connection) {
  NetworkClient client("127.0.0.1", 4444);
  connection = client.GetConnection();
  client.Listen();
}

int main() {
  SDL_Init(SDL_INIT_VIDEO);
  try {
    std::shared_ptr<Connection> connection;
    std::thread thread(networkThread,std::ref(connection));
    while(!connection) {

    }
    const Data data = std::string("11110000");
    connection->send(data);

    while(true) {

    }
    thread.join();
  }
  catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}