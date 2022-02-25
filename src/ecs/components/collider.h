#pragma once

#include <SDL.h>

#include "vector2/vector2.h"

class Collider {
 public:
  SDL_Rect box;

  void update(Vector2 position) { box = createBox(position, box); }

  SDL_Rect render(Vector2 position) { return createBox(position, box); }

  bool isHit(SDL_Rect other) {
    return box.x <= other.x + other.w && box.y <= other.y + other.h &&
           box.x + box.w >= other.x && box.y + box.h >= other.y;
  }

 private:
  SDL_Rect createBox(Vector2 position, SDL_Rect rect) {
    float offsetX = static_cast<float>(rect.w) * 0.5f;
    float offsetY = static_cast<float>(rect.h) * 0.5f;

    int x = static_cast<int>(roundf(position.x - offsetX));
    int y = static_cast<int>(roundf(position.y - offsetY));

    return SDL_Rect{x, y, rect.w, rect.h};
  }
};
