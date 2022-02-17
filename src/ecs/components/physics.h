#pragma once

#include <SDL.h>

#include "utils/utils.h"
#include "vector2/vector2.h"

struct Physics {
  bool isActive;
  float deltaVelocity;
  float deltaAcceleration;
  Vector2 velocity;
  Vector2 acceleration;
  SDL_Rect collider;

  void updateCollider(Vector2 position) {
    SDL_Point point = Utils::topLeftPoint(position, this->collider);
    collider = SDL_Rect{point.x, point.y, collider.w, collider.h};
  }
};
