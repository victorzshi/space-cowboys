#pragma once

#include <SDL.h>

#include "components/physics.h"
#include "components/sprite.h"
#include "components/transform.h"

class Entities {
 public:
  Entities();

  void initialize(int screenWidth, int screenHeight, SDL_Renderer* renderer);

  int size();
  Physics* physics();
  Sprite* sprites();
  Transform* transforms();

  void input(SDL_Event event);
  void update();
  void render(SDL_Renderer* renderer, double delay);

 private:
  static const int kMaxSize = 10000;

  int size_;
  Physics* physics_;
  Sprite* sprites_;
  Transform* transforms_;

  int createEntity();
  void addPhysics(int entity, Physics physics);
  void addSprite(int entity, Sprite sprite);
  void addTransform(int entity, Transform transform);
};
