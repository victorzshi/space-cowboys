#pragma once

#include <SDL.h>

#include <vector>

#include "ecs/components/active.h"
#include "ecs/components/ai.h"
#include "ecs/components/physics.h"
#include "ecs/components/sprite.h"
#include "ecs/components/transform.h"
#include "systems/bullet_system.h"

struct Grid {
  struct Size {
    int width;
    int height;
  };
  Size cell;
  Size gutter;
  int rows;
  int columns;
  SDL_Point center;
};

class ECS {
 public:
  ECS();

  void initialize(int screenWidth, int screenHeight, SDL_Renderer* renderer);
  void terminate();

  std::vector<int> allIds;
  std::vector<int> alienIds;
  std::vector<int> tankIds;
  std::vector<int> wallIds;

  Active* active;
  AI* ai;
  Physics* physics;
  Sprite* sprite;
  Transform* transform;

  BulletSystem bulletSystem;

  void input(SDL_Event event);
  void update();
  void render(SDL_Renderer* renderer, float delay);

  bool isOutOfBounds(SDL_Rect rect);

 private:
  static const int kMaxSize_ = 1000;

  int size_;

  int screenWidth_;
  int screenHeight_;

  SDL_Renderer* renderer_;

  int createEntity();
  void initializeAliens();
  void initializeTank();
  void initializeBullets();
  void initializeWalls();

  std::vector<Vector2> generateGridPositions(Grid grid);
};
