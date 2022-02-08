#pragma once

#include <SDL.h>

#include "vector_2/vector_2.h"

class Utilities {
 public:
  static SDL_Point getTopLeftPoint(Vector2 position, int width, int height) {
    double offsetX = position.x - width * 0.5;
    double offsetY = position.y - height * 0.5;

    SDL_Point point = {static_cast<int>(round(offsetX)),
                       static_cast<int>(round(offsetY))};

    return point;
  }
};
