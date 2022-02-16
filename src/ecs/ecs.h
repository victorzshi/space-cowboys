#pragma once

#include <SDL.h>

#include "systems/alien/alien_system.h"

class ECS {
 public:
  void initialize(int screenWidth, int screenHeight, SDL_Renderer* renderer);
  void terminate();

  void input(SDL_Event event);
  void ai();
  void update();
  void render(SDL_Renderer* renderer, float delay);

 private:
  AlienSystem alienSystem;
};
