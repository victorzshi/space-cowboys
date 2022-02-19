#pragma once

#include <SDL.h>

#include "ecs/ecs_interface.h"
#include "services/locator.h"

class ProcessInput {
 public:
  static void input(ECSInterface& ecs) {
    const Uint8* currentKeyStates = SDL_GetKeyboardState(nullptr);

    if (currentKeyStates[SDL_SCANCODE_LEFT]) {
      Locator::logger().print("Left key pressed");
    }

    if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
      Locator::logger().print("Right key pressed");
    }

    if (currentKeyStates[SDL_SCANCODE_SPACE]) {
      Locator::logger().print("Space key pressed");

      ecs.bullets().activate(ecs, ecs.bullets().active());
    }
  }
};
