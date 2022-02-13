#pragma once

#include <SDL.h>

#include "entities/entities.h"

class Game {
 public:
  Game();

  bool initialize();
  void terminate();

  void run(bool isSmokeTest = false);

 private:
  static const int kScreenWidth = 1920;
  static const int kScreenHeight = 1080;
  static const int kTicksPerUpdate = 16;
  static const int kSmokeTestDuration = 1000;

  SDL_Window* window_;
  SDL_Renderer* renderer_;
  Entities entities_;

  bool isRunning_;
};
