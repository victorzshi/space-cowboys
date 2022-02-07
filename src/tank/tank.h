#pragma once

#include <SDL.h>

#include "../vector_2/vector_2.h"

class Tank {
 public:
  Tank();

  void setPosition(Vector2 position);

  void input(SDL_Event& event);

  void update();

  void render(SDL_Renderer* renderer) const;

 private:
  const double speed_ = 0.1;

  Vector2 position_;
  Vector2 velocity_;
  Vector2 acceleration_;
};
