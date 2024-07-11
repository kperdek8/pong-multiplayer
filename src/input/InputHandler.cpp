//
// Created by kperdek8 on 10.07.2024.
//

#include "InputHandler.h"

#include <iostream>
#include <utility>
#include <ranges>

InputHandler::InputHandler(std::weak_ptr<Connection> connection1, std::weak_ptr<Connection> connection2,
                           KeyMapping keyMapping1, KeyMapping keyMapping2)
  : connection1_(std::move(connection1)), connection2_(std::move(connection2)), keyMapping1_(std::move(keyMapping1)),
    keyMapping2_(std::move(keyMapping2)) {
  // Initialize action states
  for (const Action &action: keyMapping1_.getKeyMappings() | std::views::values) {
    actionStates_[action] = false;
  }
  for (const Action &action: keyMapping2_.getKeyMappings() | std::views::values) {
    actionStates_[action] = false;
  }
}

// TODO: Improve input handling. Some inputs are lost by this function, maybe caused by application being single thread.
void InputHandler::handleInput() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    auto key = event.key.key;
    auto eventType = event.type;
    switch (event.type) {
      case SDL_EVENT_KEY_DOWN:
        handleKeyEvent(key, eventType);
        break;
      case SDL_EVENT_KEY_UP:
        handleKeyEvent(key, eventType);
        break;
      case SDL_EVENT_QUIT:
        handleQuitEvent();
        break;
    }
  }
}

bool InputHandler::isKeyPressed(const SDL_Keycode key) const {
  auto it = keyStates_.find(key);
  if (it != keyStates_.end()) {
    return it->second;
  }
  return false;
}

bool InputHandler::isActionTriggered(const Action action) const {
  auto it = actionStates_.find(action);
  if (it != actionStates_.end()) {
    return it->second;
  }
  return false;
}

void InputHandler::handleKeyEvent(const SDL_Keycode &key, const Uint32 &event) {
  std::cout << "Handling key: " << key << " Event: " << event << std::endl;
  bool isPressed = (event == SDL_EVENT_KEY_DOWN);
  keyStates_[key] = isPressed;

  // Check pressed key matches first player key mappings
  Action action = keyMapping1_.getAction(key);
  std::shared_ptr<Connection> conn = connection1_.lock();
  if (action != Action::NONE && conn) {
    conn->sendAction(action, isPressed);
    actionStates_[action] = isPressed;
    return;
  }

  // Check pressed key matches second player key mappings
  action = keyMapping2_.getAction(key);
  conn = connection2_.lock();
  if (action != Action::NONE && conn) {
    conn->sendAction(action, isPressed);
    actionStates_[action] = isPressed;
    return;
  }
}

void InputHandler::handleQuitEvent() {
  actionStates_[Action::QUIT] = true;
}
