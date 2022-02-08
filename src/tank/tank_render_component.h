#pragma once

#include "game_object/game_object.h"
#include "utilities/utilities.h"

class TankRenderComponent : public RenderComponent {
 public:
  virtual void update(GameObject& object, SDL_Renderer* renderer,
                      double delay) override {
    SDL_Point point;

    if (delay > 0) {
      Vector2 velocity = Vector2::multiply(object.velocity, delay);
      Vector2 position = Vector2::add(object.position, velocity);
      point = Utilities::getTopLeftPoint(position, object.width, object.height);
    } else {
      point = Utilities::getTopLeftPoint(object.position, object.width,
                                         object.height);
    }

    SDL_Rect box = {point.x, point.y, object.width, object.height};

    SDL_RenderDrawRect(renderer, &box);
  }
};
