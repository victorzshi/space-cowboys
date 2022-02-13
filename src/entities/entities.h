#pragma once

#include <SDL.h>

#include "components/physics.h"
#include "components/transform.h"

class Entities {
 public:
  Entities();

  void initialize(int screenWidth, int screenHeight);

  Transform* transforms;
  Physics* physics;
  int size();

  void input(SDL_Event event);
  void update();
  void render(SDL_Renderer* renderer, double delay);

 private:
  static const int kMaxSize = 10;

  int size_;

  int createEntity();
  void addTransform(int entity, Transform transform);
};
