#pragma once

#include "utils/utils.h"

struct SDL_Rect;
struct SDL_Point;
struct Vector2;

struct Collider {
  SDL_Rect box;

  void update(Vector2 position) {
    SDL_Point point = Utils::topLeftPoint(position, this->box);
    box = SDL_Rect{point.x, point.y, box.w, box.h};
  }
};
