//
// Created by kperdek8 on 07.07.2024.
//

#ifndef RENDERER_H
#define RENDERER_H

#include <SDL3/SDL_video.h>
#include <memory>

class Renderer {
public:
  Renderer& operator=(const Renderer&) = delete;
  Renderer(const Renderer &other) = delete;
  static Renderer* GetInstance();
private:
  Renderer();
  ~Renderer() = default;

  static Renderer* instance_;
  static std::mutex mutex_;
  SDL_Window* window_;
};



#endif //RENDERER_H
