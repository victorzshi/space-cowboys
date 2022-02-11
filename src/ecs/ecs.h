#pragma once

#include <SDL.h>

#include "components/transform.h"

class ECS {
 public:
  ECS();

  void input(SDL_Event event);
  void update();
  void render(SDL_Renderer* renderer, double delay);

 private:
  static const int kMaxEntities = 10;

  int totalEntities_;

  Transform* transforms;

  int createEntity();
  void addTransform(int entity, Transform transform);
};
