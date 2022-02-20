#include "input_player.h"

#include <SDL.h>

#include "ecs/components/physics.h"
#include "ecs/components/transform.h"
#include "ecs/engine.h"
#include "ecs/pools/bullets/bullets.h"
#include "ecs/pools/tanks/tanks.h"
#include "services/locator.h"

void InputPlayer::input(Engine& e) {
  Transform* transform = e.transform();
  Physics* physics = e.physics();

  float deltaAcceleration = e.tanks().DELTA_ACCELERATION;

  int begin = e.tanks().begin();
  int size = e.tanks().size();

  const Uint8* currentKeyStates = SDL_GetKeyboardState(nullptr);

  if (currentKeyStates[SDL_SCANCODE_LEFT]) {
    Locator::logger().print("Left key pressed");

    for (int i = begin; i < size; i++) {
      physics[i].acceleration.x = -deltaAcceleration;
    }
  }

  if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
    Locator::logger().print("Right key pressed");

    for (int i = begin; i < size; i++) {
      physics[i].acceleration.x = deltaAcceleration;
    }
  }

  if (currentKeyStates[SDL_SCANCODE_SPACE]) {
    Locator::logger().print("Space key pressed");

    for (int i = begin; i < size; i++) {
      int bullet = e.bullets().size();

      if (e.bullets().activate(bullet)) {
        transform[bullet].position = transform[i].position;
      }
    }
  }
}
