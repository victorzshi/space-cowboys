#pragma once

#include <SDL.h>

#include "vec2/vec2.h"

class Utils {
 public:
  static SDL_Point topLeftPoint(Vec2 position, int width, int height) {
    double offsetX = position.x - width * 0.5;
    double offsetY = position.y - height * 0.5;

    int x = static_cast<int>(round(offsetX));
    int y = static_cast<int>(round(offsetY));

    SDL_Point point = {x, y};

    return point;
  }
};
