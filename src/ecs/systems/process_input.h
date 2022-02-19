#pragma once

#include <SDL.h>

#include "services/locator.h"

class ProcessInput {
 public:
  static void input() {
    const Uint8* currentKeyStates = SDL_GetKeyboardState(nullptr);

    if (currentKeyStates[SDL_SCANCODE_LEFT]) {
      Locator::logger().print("Left");
    }

    if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
      Locator::logger().print("Right");
    }

    if (currentKeyStates[SDL_SCANCODE_SPACE]) {
      Locator::logger().print("Space");
    }
  }
};
