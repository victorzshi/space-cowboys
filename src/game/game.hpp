#pragma once

#define SDL_MAIN_HANDLED

#include <SDL.h>

class Game {
 public:
  Game();

  static bool init();

  static void start();

  static void stop();
};
