#include "render_collider.h"

#include <SDL.h>

#include "ecs/components/collider.h"
#include "ecs/engine.h"

void RenderCollider::render(Engine& e) {
  SDL_Renderer* renderer = e.renderer();

  Collider* collider = e.collider();

  Active active = e.active();

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
  for (int i = 0; i < active.size; i++) {
    int id = active.ids[i];

    SDL_RenderDrawRect(renderer, &collider[id].box);
  }
}
