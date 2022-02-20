#include "input_player.h"

#include <SDL.h>

#include "ecs/components/physics.h"
#include "ecs/components/timer.h"
#include "ecs/components/transform.h"
#include "ecs/engine.h"
#include "ecs/pools/bullets/bullets.h"
#include "ecs/pools/tanks/tanks.h"
#include "services/locator.h"

void InputPlayer::input(Engine& e) {
  const Uint8* keyboard = e.keyboard();

  Physics* physics = e.physics();
  Timer* timer = e.timer();
  Transform* transform = e.transform();

  float deltaVelocity = e.tanks().DELTA_VELOCITY;

  int begin = e.tanks().begin();
  int size = e.tanks().size();

  if (keyboard[SDL_SCANCODE_LEFT]) {
    Locator::logger().print("Left key pressed");

    for (int i = begin; i < size; i++) {
      physics[i].velocity.x = -deltaVelocity;
    }
  } else if (!keyboard[SDL_SCANCODE_LEFT]) {
    for (int i = begin; i < size; i++) {
      if (physics[i].velocity.x < 0) {
        physics[i].velocity.x = 0.0f;
      }
    }
  }

  if (keyboard[SDL_SCANCODE_RIGHT]) {
    Locator::logger().print("Right key pressed");

    for (int i = begin; i < size; i++) {
      physics[i].velocity.x = deltaVelocity;
    }
  } else if (!keyboard[SDL_SCANCODE_RIGHT]) {
    for (int i = begin; i < size; i++) {
      if (physics[i].velocity.x > 0) {
        physics[i].velocity.x = 0.0f;
      }
    }
  }

  if (keyboard[SDL_SCANCODE_SPACE]) {
    Locator::logger().print("Space key pressed");

    Uint64 cooldown = e.tanks().BULLET_COOLDOWN;

    Uint64 current = SDL_GetTicks64();

    for (int i = begin; i < size; i++) {
      if (timer[i].elapsed(current) >= cooldown) {
        int bullet = e.bullets().size();

        if (e.bullets().activate(bullet)) {
          transform[bullet].position = transform[i].position;

          timer[i].previous = current;
        }
      }
    }
  }
}
