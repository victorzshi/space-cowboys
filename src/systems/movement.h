#pragma once

#include "entities/entities.h"

class Movement {
 public:
  static void input(Entities& entities, SDL_Event event) {
    Physics* physics = entities.physics();

    for (int i = 0; i < entities.size(); i++) {
      if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
        switch (event.key.keysym.sym) {
          case SDLK_LEFT:
            physics[i].acceleration = Vec2(-physics[i].speed, 0.0);
            break;
          case SDLK_RIGHT:
            physics[i].acceleration = Vec2(physics[i].speed, 0.0);
            break;
          case SDLK_UP:
            physics[i].acceleration = Vec2(0.0, -physics[i].speed);
            break;
          case SDLK_DOWN:
            physics[i].acceleration = Vec2(0.0, physics[i].speed);
            break;
        }
      }
    }
  }
};
