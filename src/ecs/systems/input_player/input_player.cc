#include "input_player.h"

#include <SDL.h>

#include "ecs/components/transform.h"
#include "ecs/engine.h"
#include "ecs/pools/bullets/bullets.h"
#include "services/locator.h"

void InputPlayer::input(Engine& e) {
  const Uint8* currentKeyStates = SDL_GetKeyboardState(nullptr);

  if (currentKeyStates[SDL_SCANCODE_LEFT]) {
    Locator::logger().print("Left key pressed");
  }

  if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
    Locator::logger().print("Right key pressed");
  }

  if (currentKeyStates[SDL_SCANCODE_SPACE]) {
    Locator::logger().print("Space key pressed");

    Transform* transform = e.transform();

    int index = e.bullets().active();

    transform[index].position.x = static_cast<float>(e.viewport().w / 2);
    transform[index].position.y = static_cast<float>(e.viewport().h - 100);

    e.bullets().activate(e, index);
  }
}
