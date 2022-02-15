#pragma once

#include "ecs/ecs.h"
#include "utils/utils.h"

class RenderSprite {
 public:
  static void render(ECS& ecs, SDL_Renderer* renderer, float delay) {
    Physics* physics = ecs.physics();
    Transform* transforms = ecs.transforms();
    Sprite* sprites = ecs.sprites();

    for (int i = 0; i < ecs.size(); i++) {
      if (sprites[i].texture == nullptr) continue;

      Vector2 position;

      if (delay > 0) {
        Vector2 velocity = physics[i].velocity * delay;
        position = transforms[i].position + velocity;
      } else {
        position = transforms[i].position;
      }

      int width = transforms[i].width;
      int height = transforms[i].height;

      SDL_Point point = Utils::topLeftPoint(position, width, height);

      SDL_Rect box = {point.x, point.y, width, height};

      SDL_RenderCopy(renderer, sprites[i].texture, nullptr, &box);
    }
  }
};
