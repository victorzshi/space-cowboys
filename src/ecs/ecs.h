#pragma once

#include <SDL.h>

#include "components/physics.h"
#include "components/sprite.h"
#include "components/transform.h"

class ECS {
 public:
  ECS();

  void initialize(int screenWidth, int screenHeight, SDL_Renderer* renderer);
  // TODO(Victor): Add terminate() for fonts/images.

  int size();
  Physics* physics();
  Sprite* sprites();
  Transform* transforms();

  void input(SDL_Event event);
  void update();
  void render(SDL_Renderer* renderer, float delay);

 private:
  static const int kMaxSize = 20000;

  int size_;

  Physics* physics_;
  Sprite* sprites_;
  Transform* transforms_;

  int createEntity();
  void addPhysics(int entity, Physics physics);
  void addSprite(int entity, Sprite sprite);
  void addTransform(int entity, Transform transform);
};
