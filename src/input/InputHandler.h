//
// Created by kperdek8 on 10.07.2024.
//

#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <memory>
#include <unordered_map>

#include "../networking/Connection.h"
#include "KeyMapping.h"
#include "SDL3/SDL.h"
#include "../game/Action.h"
#include "../renderer/Renderer.h"

class InputHandler {
public:
  explicit InputHandler(std::weak_ptr<Connection> connection1 = std::weak_ptr<Connection>(),
                        std::weak_ptr<Connection> connection2 = std::weak_ptr<Connection>(),
                        KeyMapping keyMapping1 = KeyMapping(),
                        KeyMapping keyMapping2 = KeyMapping());

  void handleInput();

  void attach(Renderer* renderer);

  bool isKeyPressed(SDL_Keycode key) const;

  bool isActionTriggered(Action action) const;

private:
  void handleMouseMotionEvent(const SDL_MouseMotionEvent &event);

  void handleMouseButtonEvent(const SDL_MouseButtonEvent &event);

  void handleKeyEvent(const SDL_KeyboardEvent &event);

  void handleQuitEvent();

  void handleResizeEvent() const;

  Renderer* renderer_ = nullptr;

  Vector2D mousePos_;
  std::weak_ptr<Connection> connection1_;
  std::weak_ptr<Connection> connection2_;
  KeyMapping keyMapping1_;
  KeyMapping keyMapping2_;
  std::unordered_map<SDL_Keycode, bool> keyStates_;
  std::unordered_map<Uint8, bool> buttonStates_;
  std::unordered_map<Action, bool> actionStates_;
};


#endif //INPUTHANDLER_H
