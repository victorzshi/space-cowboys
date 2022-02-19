#pragma once

#include "ecs/ecs_interface.h"

class RenderCollider {
 public:
  static void render(ECSInterface& ecs) {
    SDL_Renderer* renderer = ecs.renderer();
    Collider* collider = ecs.collider();

    int begin = ecs.bullets().begin();
    int active = ecs.bullets().active();

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
    for (int id = begin; id < active; id++) {
      SDL_RenderDrawRect(renderer, &collider[id].box);
    }
  }
};
