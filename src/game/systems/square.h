#pragma once

#include "game/game.h"
#include "utilities/utilities.h"

class Square {
 public:
  static void updatePositions(Game& game, Transform* transforms) {
    for (int i = 0; i < game.totalEntities(); i++) {
      if (i % 4 == 0) transforms[i].position.x += 1.0;
      if (i % 4 == 1) transforms[i].position.x -= 1.0;
      if (i % 4 == 2) transforms[i].position.y += 1.0;
      if (i % 4 == 3) transforms[i].position.y -= 1.0;
     
    }
  }

  static void renderPositions(Game& game, Transform* transforms) {
    int width = 100;
    int height = 100;

    for (int i = 0; i < game.totalEntities(); i++) {
      Vector2 position = transforms[i].position;

      SDL_Point point = Utilities::getTopLeftPoint(position, width, height);

      SDL_Rect box = {point.x, point.y, width, height};

      SDL_RenderDrawRect(game.renderer(), &box);
    }
  }
};
