#include "render_sprite.h"

#include <SDL.h>

#include "ecs/components/collider.h"
#include "ecs/components/physics.h"
#include "ecs/components/sprite.h"
#include "ecs/components/transform.h"
#include "ecs/engine.h"
#include "ecs/pools/aliens/aliens.h"
#include "ecs/pools/bullets/bullets.h"
#include "vector2/vector2.h"

void RenderSprite::render(Engine& e, float delay) {
  renderActive(e, delay, e.bullets());
  renderActive(e, delay, e.aliens());
}

void RenderSprite::renderActive(Engine& e, float delay, Pool& pool) {
  SDL_Renderer* renderer = e.renderer();

  Collider* collider = e.collider();
  Physics* physics = e.physics();
  Sprite* sprite = e.sprite();
  Transform* transform = e.transform();

  int begin = pool.begin();
  int active = pool.active();

  for (int i = begin; i < active; i++) {
    SDL_Rect box = collider[i].box;

    if (delay > 0) {
      Vector2 velocity = physics[i].velocity * delay;
      Vector2 position = transform[i].position + velocity;

      box = collider[i].render(position);
    }

    SDL_RenderCopy(renderer, sprite[i].texture, nullptr, &box);
  }
}
