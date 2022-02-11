#pragma once

#include <SDL.h>

#include "ecs/components/transform.h"
#include "utilities/utilities.h"

class Square {
 public:
  static void updatePositions(int totalEntities, Transform* transforms) {
    for (int i = 0; i < totalEntities; i++) {
      transforms[i].position.x += 1.0;
      transforms[i].position.y += 1.0;
    }
  }

  static void renderPositions(SDL_Renderer* renderer, int totalEntities,
                              Transform* transforms) {
    int width = 100;
    int height = 100;

    for (int i = 0; i < totalEntities; i++) {
      Vector2 position = transforms[i].position;

      SDL_Point point = Utilities::getTopLeftPoint(position, width, height);

      SDL_Rect box = {point.x, point.x, width, height};

      SDL_RenderDrawRect(renderer, &box);
    }
  }
};
