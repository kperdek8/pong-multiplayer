//
// Created by kperdek8 on 10.07.2024.
//

#include "InputHandler.h"

#include <format>
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
    switch (event.type) {
      case SDL_EVENT_KEY_DOWN:
        handleKeyEvent(event.key);
        break;
      case SDL_EVENT_KEY_UP:
        handleKeyEvent(event.key);
        break;
      case SDL_EVENT_MOUSE_BUTTON_DOWN:
        handleMouseButtonEvent(event.button);
        break;
      case SDL_EVENT_MOUSE_BUTTON_UP:
        handleMouseButtonEvent(event.button);
      break;
      case SDL_EVENT_MOUSE_MOTION:
        handleMouseMotionEvent(event.motion);
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

void InputHandler::handleMouseMotionEvent(const SDL_MouseMotionEvent &event) {
  //std::cout << std::format("Handling mouse motion x: {}, y: {}", event.x, event.y)<< std::endl;
  mousePos_.x = event.x;
  mousePos_.y = event.y;
}

void InputHandler::handleMouseButtonEvent(const SDL_MouseButtonEvent &event) {
  std::cout << "Handling mouse button: " << static_cast<int>(event.button) << " Event: " << event.type << std::endl;
  bool isPressed = (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN);
  buttonStates_[event.button] = isPressed;
}

void InputHandler::handleKeyEvent(const SDL_KeyboardEvent &event) {
  std::cout << "Handling key: " << event.key << " Event: " << event.type << std::endl;
  bool isPressed = (event.type == SDL_EVENT_KEY_DOWN);
  keyStates_[event.key] = isPressed;

  // Check pressed key matches first player key mappings
  Action action = keyMapping1_.getAction(event.key);
  std::shared_ptr<Connection> conn = connection1_.lock();
  if (action != Action::NONE && conn) {
    conn->sendAction(action, isPressed);
    actionStates_[action] = isPressed;
    return;
  }

  // Check pressed key matches second player key mappings
  action = keyMapping2_.getAction(event.key);
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
