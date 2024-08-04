//
// Created by kperdek8 on 10.07.2024.
//

#include "KeyMapping.h"

KeyMapping::KeyMapping() {
  // this->setMapping(SDLK_W, Action::MOVE_UP);
  // this->setMapping(SDLK_S, Action::MOVE_DOWN);
  // this->setMapping(SDLK_P, Action::PAUSE);
  // this->setMapping(SDLK_SPACE, Action::START);
  // this->setMapping(SDLK_BACKSPACE, Action::QUIT);
}

KeyMapping::KeyMapping(const std::initializer_list<std::pair<SDL_Keycode, Action> > mappings) {
  for (const auto &[key, action]: mappings) {
    this->setMapping(key, action);
  }
}

void KeyMapping::setMapping(const SDL_Keycode key, const Action action) {
  keyMappings[key] = action;
}

Action KeyMapping::getAction(const SDL_Keycode key) const {
  const auto it = keyMappings.find(key);
  if (it != keyMappings.end()) {
    return it->second;
  }
  return Action::NONE;
}

const std::unordered_map<SDL_Keycode, Action> &KeyMapping::getKeyMappings() const {
  return keyMappings;
}
