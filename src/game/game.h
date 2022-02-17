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
  static const int kScreenWidth_ = 1920;
  static const int kScreenHeight_ = 1080;
  static const int kTicksPerUpdate_ = 16;
  static const int kSmokeTestDuration_ = 1000;

  bool isRunning_;

  SDL_Window* window_;
  SDL_Renderer* renderer_;
  ECS ecs_;
};
