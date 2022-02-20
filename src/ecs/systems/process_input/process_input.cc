#include "process_input.h"

#include <SDL.h>

#include "ecs/engine.h"
#include "ecs/pools/bullets/bullets.h"
#include "services/locator.h"

void ProcessInput::input(Engine& e) {
  const Uint8* currentKeyStates = SDL_GetKeyboardState(nullptr);

  if (currentKeyStates[SDL_SCANCODE_LEFT]) {
    Locator::logger().print("Left key pressed");
  }

  if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
    Locator::logger().print("Right key pressed");
  }

  if (currentKeyStates[SDL_SCANCODE_SPACE]) {
    Locator::logger().print("Space key pressed");

    e.bullets().activate(e, e.bullets().active());
  }
}
