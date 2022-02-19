#include "render_collider.h"

#include <SDL.h>

#include "ecs/components/collider.h"
#include "ecs/pools/bullets/bullets.h"

void RenderCollider::render(Engine& e) {
  SDL_Renderer* renderer = e.renderer();
  Collider* collider = e.collider();

  int begin = e.bullets().begin();
  int active = e.bullets().active();

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
  for (int id = begin; id < active; id++) {
    SDL_RenderDrawRect(renderer, &collider[id].box);
  }
}
