#pragma once

#include "ecs/ecs.h"

class Movement {
 public:
  static void input(ECS& ecs, SDL_Event event) {
    Physics* physics = ecs.physics();

    for (int i = 0; i < ecs.size(); i++) {
      if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
        Vector2 v;
        switch (event.key.keysym.sym) {
          case SDLK_LEFT:
            v.x = -physics[i].speed;
            v.y = 0.0;
            break;
          case SDLK_RIGHT:
            v.x = physics[i].speed;
            v.y = 0.0;
            break;
          case SDLK_UP:
            v.x = 0.0;
            v.y = -physics[i].speed;
            break;
          case SDLK_DOWN:
            v.x = 0.0;
            v.y = physics[i].speed;
            break;
        }
        physics[i].acceleration = v;
      }
    }
  }
};
