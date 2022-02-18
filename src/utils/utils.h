#pragma once

#include <SDL.h>

#include "vector2/vector2.h"

class Utils {
 public:
  static bool isEqual(float a, float b);

  // Position is the center of the rect.
  static SDL_Point topLeftPoint(Vector2 position, SDL_Rect rect);

  static SDL_Texture* createTexture(SDL_Renderer* renderer, const char* file);

 private:
  static constexpr float kEpsilon_ = 1.0f / 1000;
};
