//
// Created by kperdek8 on 07.07.2024.
//

#ifndef RENDERER_H
#define RENDERER_H

#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <vector>

class GameObject;

class Renderer {
public:
  void update(const std::vector<const GameObject *> &objects) const;

  Renderer();

private:
  void DrawObject(const GameObject *object) const;

  void PrintFPS() const;

  void CapFPS(int desiredFPS) const;

  const int MAX_FPS = 480;
  SDL_Color objectColor_{255, 255, 255, 255};
  SDL_Renderer *renderer_;
  SDL_Window *window_;
};


#endif //RENDERER_H
