//
// Created by kperdek8 on 10.07.2024.
//

#ifndef KEY_MAPPING_H
#define KEY_MAPPING_H

#include <SDL3/SDL.h>
#include <unordered_map>
#include "Action.h"

class KeyMapping {
public:
  // Constructor with default mappings
  KeyMapping();

  // Constructor to initialize mappings
  KeyMapping(std::initializer_list<std::pair<SDL_Keycode, Action>> mappings);

  void setMapping(SDL_Keycode key, Action action);

  Action getAction(SDL_Keycode key) const;

  const std::unordered_map<SDL_Keycode, Action>& getKeyMappings() const;

  Action find(SDL_Keycode key) const;

private:
  std::unordered_map<SDL_Keycode, Action> keyMappings;
};

#endif // KEY_MAPPING_H
