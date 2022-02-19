#pragma once

#include <SDL.h>

#include "utils/utils.h"
#include "vector2/vector2.h"

struct Collider {
  SDL_Rect box;

  void update(Vector2 position) {
    SDL_Point point = Utils::topLeftPoint(position, this->box);
    box = SDL_Rect{point.x, point.y, box.w, box.h};
  }
};
