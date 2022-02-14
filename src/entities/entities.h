#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include <sstream>

#include "components/physics.h"
#include "components/sprite.h"
#include "components/transform.h"
#include "texture/texture.h"

class Entities {
 public:
  Entities();

  void initialize(int screenWidth, int screenHeight, SDL_Renderer* renderer);
  // TODO(Victor): Add terminate() for fonts/images.

  int size();
  Physics* physics();
  Sprite* sprites();
  Transform* transforms();

  void input(SDL_Event event);
  void update(SDL_Renderer* renderer);
  void render(SDL_Renderer* renderer, double delay);

 private:
  // static const int kMaxSize = 10000;
  // static const int kMaxSize = 20000;
  // static const int kMaxSize = 25000;
  static const int kMaxSize = 27000;  // This is about the max for 60 fps

  int size_;
  Physics* physics_;
  Sprite* sprites_;
  Transform* transforms_;

  int createEntity();
  void addPhysics(int entity, Physics physics);
  void addSprite(int entity, Sprite sprite);
  void addTransform(int entity, Transform transform);

#ifdef DEBUG
  int start_time;
  int frame_total;
  int update_total;
  TTF_Font* debug_font;
  SDL_Color debug_font_color;
  std::stringstream frame_text;
  std::stringstream update_text;
  Texture frames_per_second_texture;
  Texture updates_per_second_texture;
#endif
};
