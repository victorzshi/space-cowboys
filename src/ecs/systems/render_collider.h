#pragma once

#include "ecs/ecs.h"

class RenderCollider {
 public:
  static void render(ECS& ecs, SDL_Renderer* renderer) {
    Collider* collider = ecs.collider();

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    for (size_t i = 0; i < ecs.allIds.size(); i++) {
      int id = ecs.allIds[i];

      SDL_RenderDrawRect(renderer, &collider[id].rect);
    }
  }
};
