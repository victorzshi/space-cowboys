#pragma once



#include "SDL.h"

class Game {
 public:
  Game();
  static bool init();
  void start();
  void stop();

 private:
  static const int m_SCREEN_WIDTH = 640;
  static const int m_SCREEN_HEIGHT = 480;
  static const int m_STAY_ALIVE = 1000;

  SDL_Window* window;
  SDL_Renderer* renderer;
};
