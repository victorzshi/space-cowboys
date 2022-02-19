#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include <cmath>

#include "vector2/vector2.h"

class Utils {
 public:
  // Position is the center of the rect.
  static SDL_Point topLeftPoint(Vector2 position, SDL_Rect rect) {
    float offsetX = static_cast<float>(rect.w) * 0.5f;
    float offsetY = static_cast<float>(rect.h) * 0.5f;

    int x = static_cast<int>(roundf(position.x - offsetX));
    int y = static_cast<int>(roundf(position.y - offsetY));

    return SDL_Point{x, y};
  }

  static bool isEqual(float a, float b, float epsilon = 1.0f / 1000) {
    return abs(a - b) <= epsilon * (abs(a) + abs(b) + 1.0f);
  }

  static SDL_Texture* createTexture(SDL_Renderer* renderer, const char* file) {
    SDL_Texture* texture = nullptr;
    SDL_Surface* surface = IMG_Load(file);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    return texture;
  }

  static bool isOutOfBounds(SDL_Rect box) {
    int topLeftX = box.x;
    int topLeftY = box.y;
    int bottomRightX = box.x + box.w;
    int bottomRightY = box.y + box.h;

    // TODO(Victor): Refactor hardcoded values.
    return topLeftX < 0 || topLeftY < 0 || bottomRightX > 1280 ||
           bottomRightY > 720;
  }
};
