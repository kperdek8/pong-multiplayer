//
// Created by kperdek8 on 27.07.2024.
//

#include <iostream>

#include "SDL3/SDL.h"
#include "NetworkServer.h"

int main() {
  SDL_Init(SDL_INIT_VIDEO);
  try
  {
    NetworkServer server(4444);
    server.Listen();
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }
  return 0;
}