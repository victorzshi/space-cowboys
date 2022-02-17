#pragma once

#include <SDL.h>

#include <vector>

#include "ecs/components/active.h"
#include "ecs/components/ai.h"
#include "ecs/components/physics.h"
#include "ecs/components/sprite.h"
#include "ecs/components/transform.h"

class ECS {
 public:
  ECS();

  void initialize(int screenWidth, int screenHeight, SDL_Renderer* renderer);
  void terminate();

  std::vector<int> allIds;
  std::vector<int> alienIds;
  std::vector<int> tankIds;
  std::vector<int> bulletIds;

  Active* active;
  AI* ai;
  Physics* physics;
  Sprite* sprite;
  Transform* transform;

  void input(SDL_Event event);
  void update();
  void render(SDL_Renderer* renderer, float delay);

  bool isOutOfBounds(SDL_Rect rect);

 private:
  static const int kMaxSize_ = 100;

  int size_;

  int screenWidth_;
  int screenHeight_;

  SDL_Renderer* renderer_;

  int createEntity();
  void initializeAliens();
  void initializeTank();
  void initializeBullets();
};
