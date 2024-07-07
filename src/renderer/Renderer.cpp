//
// Created by kperdek8 on 07.07.2024.
//

#include "Renderer.h"

#include <SDL3/SDL.h>
#include <iostream>

static constexpr std::string TITLE = "Pong";
static constexpr uint16_t WIDTH = 1080;
static constexpr uint16_t HEIGHT = 720;

Renderer* Renderer::instance_;
std::mutex Renderer::mutex_;

Renderer* Renderer::GetInstance() {
  std::lock_guard<std::mutex> lock(mutex_);
  if (instance_ == nullptr) {
    instance_ = new Renderer();
  }
  return instance_;
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
};