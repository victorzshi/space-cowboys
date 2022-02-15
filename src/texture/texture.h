#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include <string>

#include "vector2/vector2.h"

class Texture {
 public:
  Texture();

  SDL_Rect rect;

  void setText(SDL_Renderer* renderer, TTF_Font* font, std::string text,
               SDL_Color color);

  void render(SDL_Renderer* renderer);

  void free();

 private:
  SDL_Texture* texture_;
};
