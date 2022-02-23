#include "input_player.h"

#include <SDL.h>

#include "ecs/components/physics.h"
#include "ecs/components/timer.h"
#include "ecs/components/transform.h"
#include "ecs/engine.h"
#include "ecs/pools/bullets/bullets.h"
#include "ecs/pools/tanks/tanks.h"

void InputPlayer::input(Engine& e) {
  const Uint8* keyboard = e.keyboard();

  Physics* physics = e.physics();
  Timer* timer = e.timer();
  Transform* transform = e.transform();

  float deltaVelocity = e.tanks().DELTA_VELOCITY;

  int begin = e.tanks().begin();
  int size = e.tanks().size();

  if (keyboard[SDL_SCANCODE_UP] || keyboard[SDL_SCANCODE_W]) {
    for (int i = begin; i < size; i++) {
      physics[i].velocity.y = -deltaVelocity;
    }
  } else if (!keyboard[SDL_SCANCODE_UP] && !keyboard[SDL_SCANCODE_W]) {
    for (int i = begin; i < size; i++) {
      if (physics[i].velocity.y < 0) {
        physics[i].velocity.y = 0.0f;
      }
    }
  }

  if (keyboard[SDL_SCANCODE_DOWN] || keyboard[SDL_SCANCODE_S]) {
    for (int i = begin; i < size; i++) {
      physics[i].velocity.y = deltaVelocity;
    }
  } else if (!keyboard[SDL_SCANCODE_DOWN] && !keyboard[SDL_SCANCODE_S]) {
    for (int i = begin; i < size; i++) {
      if (physics[i].velocity.y > 0) {
        physics[i].velocity.y = 0.0f;
      }
    }
  }

  if (keyboard[SDL_SCANCODE_LEFT] || keyboard[SDL_SCANCODE_A]) {
    for (int i = begin; i < size; i++) {
      physics[i].velocity.x = -deltaVelocity;
    }
  } else if (!keyboard[SDL_SCANCODE_LEFT] && !keyboard[SDL_SCANCODE_A]) {
    for (int i = begin; i < size; i++) {
      if (physics[i].velocity.x < 0) {
        physics[i].velocity.x = 0.0f;
      }
    }
  }

  if (keyboard[SDL_SCANCODE_RIGHT] || keyboard[SDL_SCANCODE_D]) {
    for (int i = begin; i < size; i++) {
      physics[i].velocity.x = deltaVelocity;
    }
  } else if (!keyboard[SDL_SCANCODE_RIGHT] && !keyboard[SDL_SCANCODE_D]) {
    for (int i = begin; i < size; i++) {
      if (physics[i].velocity.x > 0) {
        physics[i].velocity.x = 0.0f;
      }
    }
  }

  if (keyboard[SDL_SCANCODE_SPACE]) {
    Uint64 cooldown = e.tanks().BULLET_COOLDOWN;

    Uint64 current = SDL_GetTicks64();

    for (int i = begin; i < size; i++) {
      if (timer[i].elapsed(current) >= cooldown) {
        int id = e.bullets().size();
        if (e.bullets().activate(id)) {
          transform[id].position = transform[i].position;

          timer[i].previous = current;
        }
      }
    }
  }
}
