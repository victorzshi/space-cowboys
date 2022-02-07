#pragma once

#include "../game_object/game_object.h"

class TankInputComponent : public InputComponent {
 public:
   virtual void update(GameObject& object, SDL_Event event) override {
    if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
      switch (event.key.keysym.sym) {
        case SDLK_LEFT:
          object.acceleration = Vector2(-speed_, 0.0);
          break;
        case SDLK_RIGHT:
          object.acceleration = Vector2(speed_, 0.0);
          break;
      }
    } else if (event.type == SDL_KEYUP && event.key.repeat == 0) {
      object.acceleration = Vector2(0.0, 0.0);
      object.velocity = Vector2(0.0, 0.0);
    }
  }

 private:
  const double speed_ = 0.1;
};
