#pragma once

#include "entities/entities.h"
#include "utils/utils.h"

class RenderSprite {
 public:
  static void render(Entities& entities, SDL_Renderer* renderer, double delay) {
    Physics* physics = entities.physics();
    Transform* transforms = entities.transforms();
    Sprite* sprites = entities.sprites();

    for (int i = 0; i < entities.size(); i++) {
      if (sprites[i].texture == nullptr) continue;

      Vec2 position;

      if (delay > 0) {
        Vec2 velocity = Vec2::multiply(physics[i].velocity, delay);
        position = Vec2::add(transforms[i].position, velocity);
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
