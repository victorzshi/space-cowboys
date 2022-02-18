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
    Transform* transform = ecs.transform;

    int tank = ecs.tankIds[0];

    ecs.bulletSystem.activateBullet(transform[tank].position);
  }
};
