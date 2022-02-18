#pragma once

#include <SDL.h>

#include "vector2/vector2.h"

class Utils {
 public:
  // Position is the center of the rect.
  static SDL_Point topLeftPoint(Vector2 position, SDL_Rect rect);

  static SDL_Texture* createTexture(SDL_Renderer* renderer, const char* file);
};
