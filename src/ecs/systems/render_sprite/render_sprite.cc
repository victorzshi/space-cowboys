#include "render_sprite.h"

#include <SDL.h>

#include "ecs/components/collider.h"
#include "ecs/components/physics.h"
#include "ecs/components/sprite.h"
#include "ecs/components/transform.h"
#include "ecs/pools/bullets/bullets.h"
#include "vector2/vector2.h"

void RenderSprite::render(Engine& e, float delay) {
  SDL_Renderer* renderer = e.renderer();

  Collider* collider = e.collider();
  Physics* physics = e.physics();
  Sprite* sprite = e.sprite();
  Transform* transform = e.transform();

  int begin = e.bullets().begin();
  int active = e.bullets().active();
  for (int id = begin; id < active; id++) {
    SDL_Rect box = collider[id].box;

    if (delay > 0) {
      Vector2 velocity = physics[id].velocity * delay;
      Vector2 position = transform[id].position + velocity;

      box = collider[id].render(position);
    }

    SDL_RenderCopy(renderer, sprite[id].texture, nullptr, &box);
  }
}
