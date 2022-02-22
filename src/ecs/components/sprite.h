#pragma once

#include <SDL.h>

struct SDL_Texture;

struct Sprite {
  SDL_Texture* texture;
  SDL_Rect target;
};
