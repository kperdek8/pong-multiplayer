//
// Created by kperdek8 on 27.07.2024.
//

#include <iostream>

#include "SDL3_net/SDL_net.h"
#include "SDL3/SDL.h"

int main() {
  SDL_Init(SDL_INIT_VIDEO);
  SDLNet_Init();
  std::cout<<"Test"<<std::endl;
  return 0;
}