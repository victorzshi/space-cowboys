#pragma once

#include "ecs/ecs.h"

class RenderSprite {
 public:
  static void render(ECS& ecs, SDL_Renderer* renderer, float delay) {
    Physics* physics = ecs.physics();
    Transform* transform = ecs.transform();
    Collider* collider = ecs.collider();
    Sprite* sprite = ecs.sprite();

    for (int i = 0; i < ecs.size(); i++) {
      if (sprite[i].texture == nullptr) continue;

      SDL_Rect rect;

      if (delay > 0) {
        Vector2 velocity = physics[i].velocity * delay;
        Vector2 position = transform[i].position + velocity;

        SDL_Point point = Utils::topLeftPoint(position, collider[i].rect);

        rect = {point.x, point.y, collider[i].rect.w, collider[i].rect.h};
      } else {
        rect = collider[i].rect;
      }

      SDL_RenderCopy(renderer, sprite[i].texture, nullptr, &rect);
    }
  }
};
