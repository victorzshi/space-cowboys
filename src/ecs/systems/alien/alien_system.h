#pragma once

#include <SDL.h>

#include "ecs/components/ai.h"
#include "ecs/components/collider.h"
#include "ecs/components/physics.h"
#include "ecs/components/sprite.h"
#include "ecs/components/transform.h"

class AlienSystem {
 public:
  AlienSystem();

  void initialize(int screenWidth, int screenHeight, SDL_Renderer* renderer);
  void terminate();

  void updateDirection();
  void updatePosition();
  void renderSprite(SDL_Renderer* renderer, float delay);
  void renderCollider(SDL_Renderer* renderer);

 private:
  static const int kMaxSize_ = 55;

  int size_;

  AI* ai_;
  Collider* collider_;
  Physics* physics_;
  Sprite* sprite_;
  Transform* transform_;

  bool isOutOfBounds();
};
