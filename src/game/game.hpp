#pragma once

#include "SDL.h"

class Game {
 public:
  Game(bool isSmokeTest = false);
  static bool initialize();
  void start();
  void stop();
  void processInput();
  void update();
  void render();

 private:
  static const int kScreenWidth = 640;
  static const int kScreenHeight = 480;
  static const int kTicksPerUpdate = 16;
  static const int kSmokeTestDuration = 1000;

  bool isSmokeTest_;
  bool isRunning_;

  SDL_Window* window_;
  SDL_Renderer* renderer_;
};
