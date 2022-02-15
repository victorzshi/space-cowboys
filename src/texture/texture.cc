#include "texture.h"

#include <SDL_ttf.h>

#include "utils/utils.h"

Texture::Texture() : rect({0, 0, 0, 0}), texture_(nullptr) {}

void Texture::setText(SDL_Renderer* renderer, TTF_Font* font, std::string text,
                      SDL_Color color) {
  free();

  SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);

  rect.w = surface->w;
  rect.h = surface->h;
  texture_ = SDL_CreateTextureFromSurface(renderer, surface);

  SDL_FreeSurface(surface);
}

void Texture::render(SDL_Renderer* renderer) {
  SDL_RenderCopy(renderer, texture_, nullptr, &rect);
}

void Texture::free() {
  if (texture_ != nullptr) {
    SDL_DestroyTexture(texture_);
    texture_ = nullptr;
    rect = {0, 0, 0, 0};
  }
}
