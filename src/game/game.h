#pragma once

#include <SDL.h>

#include "ecs/ecs.h"

class Game {
 public:
  Game();

  bool initialize();
  void terminate();

  void run(bool isSmokeTest = false);

 private:
  static const int SCREEN_WIDTH = 1280;
  static const int SCREEN_HEIGHT = 720;
  static const int TICKS_PER_UPDATE = 16;
  static const int SMOKE_TEST_DURATION = 1000;

  bool isRunning_;

  SDL_Window* window_;
  SDL_Renderer* renderer_;

  ECS ecs_;
};
