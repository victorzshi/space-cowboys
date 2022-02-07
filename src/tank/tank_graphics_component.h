#pragma once

#include "../game_object/game_object.h"

class TankGraphicsComponent : public GraphicsComponent {
 public:
   virtual void update(GameObject& object, SDL_Renderer* renderer) override {
    int x = static_cast<int>(round(object.position.x));
    int y = static_cast<int>(round(object.position.y));
    const int width = 100;
    const int height = 100;

    SDL_Rect box = {x, y, width, height};

    SDL_RenderFillRect(renderer, &box);
  }
};
