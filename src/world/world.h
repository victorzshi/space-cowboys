#pragma once

#include <SDL.h>

#include "components/physics.h"
#include "components/transform.h"

class World {
 public:
  World();

  bool initialize();
  void terminate();

  SDL_Renderer* renderer();
  int totalEntities();

  void run(bool isSmokeTest = false);

 private:
  static const int kScreenWidth = 640;
  static const int kScreenHeight = 480;
  static const int kTicksPerUpdate = 16;
  static const int kSmokeTestDuration = 1000;
  static const int kMaxEntities = 10;

  SDL_Window* window_;
  SDL_Renderer* renderer_;

  bool isRunning_;
  int totalEntities_;

  Transform* transforms_;
  Physics* physics_;

  void input();
  void update();
  void render(double delay);

  int createEntity();
  void addTransform(int entity, Transform transform);
};
