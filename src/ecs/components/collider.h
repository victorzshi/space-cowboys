#pragma once

#include <SDL.h>

#include "vector2/vector2.h"

struct Collider {
  SDL_Rect box;

  void update(Vector2 position) {
    float offsetX = static_cast<float>(box.w) * 0.5f;
    float offsetY = static_cast<float>(box.h) * 0.5f;

    int x = static_cast<int>(roundf(position.x - offsetX));
    int y = static_cast<int>(roundf(position.y - offsetY));

    box = SDL_Rect{x, y, box.w, box.h};
  }
};
