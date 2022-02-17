#pragma once

#include "ecs/ecs.h"

class ProcessTankInput {
 public:
  static void input(ECS& ecs, SDL_Event event) {
    Physics* physics = ecs.physics();

    int id = ecs.tankIds[0];

    if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
      switch (event.key.keysym.sym) {
        case SDLK_LEFT:
          physics[id].acceleration.x = -physics[id].deltaAcceleration;
          break;
        case SDLK_RIGHT:
          physics[id].acceleration.x = physics[id].deltaAcceleration;
          break;
      }
    } else if (event.type == SDL_KEYUP && event.key.repeat == 0) {
      physics[id].acceleration.x = 0.0f;
      physics[id].velocity.x = 0.0f;
    }
  }
};
