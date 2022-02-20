#include "render_collider.h"

#include <SDL.h>

#include "ecs/components/collider.h"
#include "ecs/engine.h"
#include "ecs/pools/aliens/aliens.h"
#include "ecs/pools/bullets/bullets.h"

void RenderCollider::render(Engine& e) {
  renderActive(e, e.aliens());
  renderActive(e, e.bullets());
}

void RenderCollider::renderActive(Engine& e, Pool& pool) {
  SDL_Renderer* renderer = e.renderer();

  Collider* collider = e.collider();

  int begin = pool.begin();
  int size = pool.size();

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
  for (int i = begin; i < size; i++) {
    SDL_RenderDrawRect(renderer, &collider[i].box);
  }
}
