//
// Created by kperdek8 on 07.07.2024.
//

#include "Renderer.h"
#include "../game/GameObjects.h"

#include <SDL3/SDL.h>
#include <iostream>

static constexpr std::string TITLE = "Pong";
static constexpr uint16_t WIDTH = 1920;
static constexpr uint16_t HEIGHT = 1080;

void Renderer::update(const std::vector<const GameObject *> &objects) const {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    break;
  }
  SDL_SetRenderDrawColor(renderer_, 0x00, 0x00, 0x00, 0x00);
  SDL_RenderClear(renderer_);
  for (auto &object: objects) {
    DrawObject(object);
  }

  SDL_RenderPresent(renderer_);
}

Renderer::Renderer() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
  }
  window_ = SDL_CreateWindow(TITLE.c_str(), WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
  if (!window_) {
    std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
    SDL_Quit();
  }
  renderer_ = SDL_CreateRenderer(window_, NULL);
  if (!renderer_) {
    std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
    SDL_DestroyWindow(window_);
    SDL_Quit();
  }
}

void Renderer::DrawObject(const GameObject *object) const {
  const SDL_FRect rect = {object->getX(), object->getY(), object->width, object->height};
  SDL_SetRenderDrawColor(renderer_, objectColor_.r, objectColor_.g, objectColor_.b, objectColor_.a);
  SDL_RenderFillRect(renderer_, &rect);
};
