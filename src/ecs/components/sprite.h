#pragma once

#include <SDL.h>

struct SDL_Texture;

class Sprite {
 public:
  SDL_Texture* texture;
  SDL_Rect target;
};
