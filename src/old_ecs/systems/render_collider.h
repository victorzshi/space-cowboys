#pragma once

#include "ecs/ecs.h"

class RenderCollider {
 public:
  static void render(ECS& ecs, SDL_Renderer* renderer) {
    Active* active = ecs.active;
    Physics* physics = ecs.physics;

    for (size_t i = 0; i < ecs.allIds.size(); i++) {
      int id = ecs.allIds[i];

      if (active[id].isActive()) {
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawRect(renderer, &physics[id].collider);
      }

      else if (active[id].isNotActive()) {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawRect(renderer, &physics[id].collider);
      }
    }
  }
};