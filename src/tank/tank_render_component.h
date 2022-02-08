#pragma once

#include "game_object/game_object.h"
#include "utilities/utilities.h"

class TankRenderComponent : public RenderComponent {
 public:
  virtual void update(GameObject& object, SDL_Renderer* renderer,
                      double delay) override {
    // TODO(Victor): Account for delay.
    (void)delay;

    SDL_Point point = Utilities::getTopLeftPoint(object.position, object.width,
                                                 object.height);

    SDL_Rect box = {point.x, point.y, object.width, object.height};

    SDL_RenderDrawRect(renderer, &box);
  }
};
