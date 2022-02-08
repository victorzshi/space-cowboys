#pragma once

#include <SDL.h>

#include "game_object/game_object.h"

class Game {
 public:
  Game();
  bool initialize();
  void start(bool isSmokeTest = false);
  void stop();
  void input();
  void update();
  void render(double delay);

 private:
  static const int kScreenWidth = 640;
  static const int kScreenHeight = 480;
  static const int kTicksPerUpdate = 16;
  static const int kSmokeTestDuration = 1000;
  static const int kMaxObjects = 2;

  bool isRunning_;

  SDL_Window* window_;
  SDL_Renderer* renderer_;

  GameObject* objects[kMaxObjects];
};
