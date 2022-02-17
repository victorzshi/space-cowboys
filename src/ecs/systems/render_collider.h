#pragma once

#include "ecs/ecs.h"

class RenderCollider {
 public:
  static void render(ECS& ecs, SDL_Renderer* renderer) {
    Collider* collider = ecs.collider();

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    for (int i = 0; i < ecs.size(); i++) {
      SDL_RenderDrawRect(renderer, &collider[i].rect);
    }
  }
};
