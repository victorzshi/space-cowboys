#pragma once

#include <SDL.h>

#include "utils/utils.h"

struct Collider {
  SDL_Rect rect;

  void update(Vector2 position) {
    SDL_Point point = Utils::topLeftPoint(position, this->rect);
    rect = SDL_Rect{point.x, point.y, rect.w, rect.h};
  }
};
