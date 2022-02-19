#pragma once

#include "ecs/engine.h"

class RenderCollider {
 public:
  static void render(Engine& e) {
    SDL_Renderer* renderer = e.renderer();
    Collider* collider = e.collider();

    int begin = e.bullets().begin();
    int active = e.bullets().active();

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
    for (int id = begin; id < active; id++) {
      SDL_RenderDrawRect(renderer, &collider[id].box);
    }
  }
};
