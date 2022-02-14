#pragma once

#include <SDL.h>

#include <cmath>

#include "vector2/vector2.h"

class Utils {
 public:
  static SDL_Point topLeftPoint(Vector2 position, int width, int height) {
    float offsetX = static_cast<float>(width * 0.5);
    float offsetY = static_cast<float>(height * 0.5);

    int x = static_cast<int>(roundf(position.x - offsetX));
    int y = static_cast<int>(roundf(position.y - offsetY));

    SDL_Point point = {x, y};

    return point;
  }

  static bool isEqual(float a, float b, float epsilon = 1.0f / 1000) {
    return abs(a - b) <= epsilon * (abs(a) + abs(b) + 1.0f);
  }
};
