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
  void update(const std::vector<const GameObject *> &objects);

  Renderer();

private:
  void DrawObject(const GameObject *object, float scale) const;

  void PrintFPS() const;

  void CapFPS(int desiredFPS) const;

  void UpdateViewport();

  const int MAX_FPS = 480;

  int windowWidth_{0};
  int windowHeight_{0};

  // For viewport scale calculation
  constexpr static float TARGET_WIDTH = 1920.0f;
  constexpr static float TARGET_HEIGHT = 1080.0f;
  constexpr static float TARGET_ASPECT_RATIO = TARGET_WIDTH / TARGET_HEIGHT;
  constexpr static float MARGIN_FACTOR = 0.05f;

  SDL_Color objectColor_{255, 255, 255, 255};
  SDL_Renderer *renderer_;
  SDL_Window *window_;
  SDL_Rect viewport_;
};


#endif //RENDERER_H
