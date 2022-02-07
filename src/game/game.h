#pragma once

#include "../tank/tank.h"
#include "SDL.h"

class Game {
 public:
  Game();
  bool initialize();
  void start(bool isSmokeTest = false);
  void stop();
  void processInput();
  void update();
  void render();

 private:
  static const int kScreenWidth = 640;
  static const int kScreenHeight = 480;
  static const int kTicksPerUpdate = 16;
  static const int kSmokeTestDuration = 1000;

  bool isRunning_;

  SDL_Window* window_;
  SDL_Renderer* renderer_;

  Tank tank_;
};
