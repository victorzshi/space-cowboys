#pragma once

#include "ecs/ecs.h"

class ProcessTankInput {
 public:
  static void input(ECS& ecs, SDL_Event event) {
    Active* active = ecs.active;
    Physics* physics = ecs.physics;

    int id = ecs.tankIds[0];

    if (active[id].isNotActive()) return;

    if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
      switch (event.key.keysym.sym) {
        case SDLK_LEFT:
          physics[id].acceleration.x = -physics[id].deltaAcceleration;
          break;
        case SDLK_RIGHT:
          physics[id].acceleration.x = physics[id].deltaAcceleration;
          break;
        case SDLK_SPACE:
          shootBullet(ecs);
          break;
      }
    } else if (event.type == SDL_KEYUP) {
      switch (event.key.keysym.sym) {
        case SDLK_LEFT:
          physics[id].acceleration.x = 0.0f;
          physics[id].velocity.x = 0.0f;
          break;
        case SDLK_RIGHT:
          physics[id].acceleration.x = 0.0f;
          physics[id].velocity.x = 0.0f;
          break;
      }
    }
  }

 private:
  static void shootBullet(ECS& ecs) {
    Active* active = ecs.active;
    Transform* transform = ecs.transform;
    Physics* physics = ecs.physics;

    for (size_t i = 0; i < ecs.bulletIds.size(); i++) {
      int bullet = ecs.bulletIds[i];

      if (active[bullet].isNotActive()) {
        int tank = ecs.tankIds[0];

        active[bullet].state = true;
        physics[bullet].velocity.y = -physics[bullet].deltaVelocity;
        transform[bullet].position = transform[tank].position;

        break;
      }
    }
  }
};
