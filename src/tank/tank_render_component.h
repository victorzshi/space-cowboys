#pragma once

#include "game_object/game_object.h"

class TankRenderComponent : public RenderComponent {
 public:
  virtual void update(GameObject& object, SDL_Renderer* renderer,
                      double delay) override {
    // TODO(Victor): Account for delay.
    (void)delay;

    SDL_Rect box;

    // Return SDL_Point
    box.x = static_cast<int>(round(object.position.x));
    box.y = static_cast<int>(round(object.position.y));
    box.w = object.width;
    box.h = object.height;

    SDL_RenderFillRect(renderer, &box);
  }
};
