#pragma once

#include "../game/game.h"

class Tank {
 public:
  Tank();

  void update(Game& game, SDL_Renderer* renderer);

 private:
  static const int ACCELERATION = 1;

  int velocity_;
  int x_, y_;
};