#include "tank.h"

Tank::Tank() : position_(Vector2()), velocity_(Vector2()) {}

void Tank::setPosition(Vector2 position) { position_ = position; }

void Tank::input(SDL_Event& event) {
  if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
    switch (event.key.keysym.sym) {
      case SDLK_LEFT:
        acceleration_ = Vector2(-speed_, 0.0);
        break;
      case SDLK_RIGHT:
        acceleration_ = Vector2(speed_, 0.0);
        break;
    }
  } else if (event.type == SDL_KEYUP && event.key.repeat == 0) {
    acceleration_ = Vector2(0.0, 0.0);
    velocity_ = Vector2(0.0, 0.0);
  }
}

void Tank::update() {
  velocity_ = Vector2::add(velocity_, acceleration_);

  position_ = Vector2::add(position_, velocity_);
}

void Tank::render(SDL_Renderer* renderer) const {
  int x = static_cast<int>(round(position_.x));
  int y = static_cast<int>(round(position_.y));
  const int width = 100;
  const int height = 100;

  SDL_Rect box = {x, y, width, height};

  SDL_RenderFillRect(renderer, &box);
}
