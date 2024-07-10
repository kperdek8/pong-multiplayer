//
// Created by kperdek8 on 10.07.2024.
//

#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <memory>
#include <unordered_map>

#include "Connection.h"
#include "KeyMapping.h"
#include "SDL3/SDL.h"
#include "../game/Action.h"

class InputHandler {
public:
  explicit InputHandler(std::weak_ptr<Connection> connection1 = std::weak_ptr<Connection>(),
                        std::weak_ptr<Connection> connection2 = std::weak_ptr<Connection>(),
                        KeyMapping keyMapping1 = KeyMapping(),
                        KeyMapping keyMapping2 = KeyMapping());

  void handleInput();

  bool isKeyPressed(SDL_Keycode key) const;

  bool isActionTriggered(Action action) const;

private:
  void handleKeyEvent(const SDL_Keycode &key, const Uint32 &event); // For Uint32 reason, refer to SDL3's SDL_Event documentation

  void handleQuitEvent();

  std::weak_ptr<Connection> connection1_;
  std::weak_ptr<Connection> connection2_;
  KeyMapping keyMapping1_;
  KeyMapping keyMapping2_;
  std::unordered_map<SDL_Keycode, bool> keyStates_;
  std::unordered_map<Action, bool> actionStates_;
};


#endif //INPUTHANDLER_H
