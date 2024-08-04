//
// Created by kperdek8 on 07.07.2024.
//

#include "Renderer.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
#include <iostream>
#include "../game/GameObjects.h"

static constexpr std::string TITLE = "Pong";
static constexpr uint16_t WIDTH = 1080;
static constexpr uint16_t HEIGHT = 720;

Renderer::Renderer() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
  }
  window_ = SDL_CreateWindow(TITLE.c_str(), WIDTH, HEIGHT,
                             SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED);
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

  SDL_GetRenderOutputSize(renderer_, &windowWidth_, &windowHeight_);
  UpdateViewport();
}

void Renderer::Update(const std::vector<const GameObject *> &objects) {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      default:
        break;
    }
  }
  SDL_SetRenderDrawColor(renderer_, 0x00, 0x00, 0x00, 0x00);
  SDL_RenderClear(renderer_);

  float scale = std::min(static_cast<float>(viewport_.w) / TARGET_WIDTH,
                         static_cast<float>(viewport_.h) / TARGET_HEIGHT);

  for (auto &object: objects) {
    DrawObject(object, scale);
  }

  SDL_RenderPresent(renderer_);
  CapFPS(MAX_FPS);
  CountFPS();
}

void Renderer::DrawObject(const GameObject *object, const float scale) const {
  const SDL_FRect rect = {
    object->getX() * scale,
    object->getY() * scale,
    object->width * scale,
    object->height * scale
  };
  SDL_SetRenderDrawColor(renderer_, objectColor_.r, objectColor_.g, objectColor_.b, objectColor_.a);
  SDL_RenderFillRect(renderer_, &rect);
}

int Renderer::GetFPS() const {
  return currentFps_;
}

void Renderer::CountFPS() {
  static Uint32 lastTime = 0;
  static int frameCount = 0;

  const Uint32 currentTime = SDL_GetTicks();
  frameCount++;

  if (currentTime > lastTime + 1000) {
    // Update FPS every second
    currentFps_ = frameCount;
    frameCount = 0;
    lastTime = currentTime;
  }
}

void Renderer::CapFPS(const int desiredFPS) const {
  static Uint32 frameStart = SDL_GetTicks();
  const Uint32 frameTime = SDL_GetTicks() - frameStart;

  const int frameDelay = 1000 / desiredFPS;
  if (frameDelay > frameTime) {
    SDL_Delay(frameDelay - frameTime);
  }

  frameStart = SDL_GetTicks();
}

void Renderer::UpdateViewport() {
  SDL_GetRenderOutputSize(renderer_, &windowWidth_, &windowHeight_);

  float marginWidth = windowWidth_ * MARGIN_FACTOR;
  float marginHeight = windowHeight_ * MARGIN_FACTOR;
  float effectiveWidth = windowWidth_ - 2 * marginWidth;
  float effectiveHeight = windowHeight_ - 2 * marginHeight;

  float currentAspectRatio = static_cast<float>(windowWidth_) / static_cast<float>(windowHeight_);

  if (currentAspectRatio > TARGET_ASPECT_RATIO) {
    effectiveWidth = effectiveHeight * TARGET_ASPECT_RATIO;
    marginWidth = (windowWidth_ - effectiveWidth) / 2.0f;
  } else {
    effectiveHeight = effectiveWidth / TARGET_ASPECT_RATIO;
    marginHeight = (windowHeight_ - effectiveHeight) / 2.0f;
  }

  viewport_ = {
    static_cast<int>(marginWidth),
    static_cast<int>(marginHeight),
    static_cast<int>(effectiveWidth),
    static_cast<int>(effectiveHeight)
  };

  //std::cout<<std::format("Viewport aspect ratio: {}", currentAspectRatio)<<std::endl;
  //std::cout<<std::format("Margin width: {} Margin height: {}", marginWidth, marginHeight)<<std::endl;

  SDL_SetRenderViewport(renderer_, &viewport_);
}


