#include "texture.h"

#include <SDL_ttf.h>

Texture::Texture() {
  texture = nullptr;

  width = 0;
  height = 0;
}

void Texture::load_text(SDL_Renderer* renderer, TTF_Font* font,
                        std::string text, SDL_Color color) {
  free();

  SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);

  texture = SDL_CreateTextureFromSurface(renderer, surface);

  width = surface->w;
  height = surface->h;

  SDL_FreeSurface(surface);
}

int Texture::get_width() { return width; }

int Texture::get_height() { return height; }

void Texture::render(SDL_Renderer* renderer, int x, int y) {
  SDL_Rect render_target = {x, y, width, height};

  SDL_RenderCopy(renderer, texture, nullptr, &render_target);
}

void Texture::free() {
  if (texture != nullptr) {
    SDL_DestroyTexture(texture);
    texture = nullptr;
    width = 0;
    height = 0;
  }
}
