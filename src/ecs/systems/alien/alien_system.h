#pragma once

#include <SDL.h>

#include "ecs/components/collider.h"
#include "ecs/components/physics.h"
#include "ecs/components/sprite.h"
#include "ecs/components/transform.h"

class AlienSystem {
 public:
  AlienSystem();

  void initialize(int screenWidth, int screenHeight, SDL_Renderer* renderer);
  void terminate();

  void input(SDL_Event event);
  void updatePosition();
  void renderSprite(SDL_Renderer* renderer, float delay);
  void renderCollider(SDL_Renderer* renderer);

 private:
  static const int kMaxSize_ = 55;

  int size_;

  Collider* colliders_;
  Physics* physics_;
  Sprite* sprites_;
  Transform* transforms_;
};
