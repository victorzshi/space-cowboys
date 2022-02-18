#include "utils.h"

#include <SDL_image.h>

SDL_Point Utils::topLeftPoint(Vector2 position, SDL_Rect rect) {
  float offsetX = static_cast<float>(rect.w) * 0.5f;
  float offsetY = static_cast<float>(rect.h) * 0.5f;

  int x = static_cast<int>(roundf(position.x - offsetX));
  int y = static_cast<int>(roundf(position.y - offsetY));

  return SDL_Point{x, y};
}

SDL_Texture* Utils::createTexture(SDL_Renderer* renderer, const char* file) {
  SDL_Texture* texture = nullptr;
  SDL_Surface* surface = IMG_Load(file);
  texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);

  return texture;
}
