#pragma once

#include <SDL.h>

#include <vector>

#include "ecs/components/active.h"
#include "ecs/components/ai.h"
#include "ecs/components/physics.h"
#include "ecs/components/sprite.h"
#include "ecs/components/transform.h"

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
  std::vector<int> bulletIds;
  std::vector<int> wallIds;

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
  static const int kMaxSize_ = 1000;

  int size_;

  int screenWidth_;
  int screenHeight_;

  SDL_Renderer* renderer_;

  int createEntity();
  void initializeAliens(SDL_Point center, int rows, int columns, int alienWidth,
                        float alienDeltaVelocity);
  void initializeTank(SDL_Point center, int tankWidth,
                      float tankDeltaAcceleration);
  void initializeBullets(int totalBullets, int bulletWidth,
                         float bulletDeltaVelocity);
  void initializeWalls(SDL_Point center, int totalWalls, int rows, int columns,
                       int wallWidth);

  std::vector<Vector2> generateGridPositions(Grid grid);
};
