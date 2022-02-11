#pragma once

#include "game/game.h"
#include "utilities/utilities.h"

class Square {
 public:
  static void inputPositions(Game& game, SDL_Event event, Physics* physics) {
    double speed = 0.1;

    for (int i = 0; i < game.totalEntities(); i++) {
      if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
        switch (event.key.keysym.sym) {
          case SDLK_LEFT:
            physics[i].acceleration = Vector2(-speed, 0.0);
            break;
          case SDLK_RIGHT:
            physics[i].acceleration = Vector2(speed, 0.0);
            break;
          case SDLK_UP:
            physics[i].acceleration = Vector2(0.0, -speed);
            break;
          case SDLK_DOWN:
            physics[i].acceleration = Vector2(0.0, speed);
            break;
        }
      } else if (event.type == SDL_KEYUP && event.key.repeat == 0) {
        physics[i].acceleration = Vector2(0.0, 0.0);
        physics[i].velocity = Vector2(0.0, 0.0);
      }
    }
  }

  static void updatePositions(Game& game, Transform* transforms,
                              Physics* physics) {
    for (int i = 0; i < game.totalEntities(); i++) {
      physics[i].velocity =
          Vector2::add(physics[i].velocity, physics[i].acceleration);

      transforms[i].position =
          Vector2::add(transforms[i].position, physics[i].velocity);
    }
  }

  static void renderPositions(Game& game, double delay, Transform* transforms,
                              Physics* physics) {
    int width = 100;
    int height = 100;

    for (int i = 0; i < game.totalEntities(); i++) {
      SDL_Point point;

      if (delay > 0) {
        Vector2 velocity = Vector2::multiply(physics[i].velocity, delay);
        Vector2 position = Vector2::add(transforms[i].position, velocity);
        point = Utilities::getTopLeftPoint(position, width, height);
      } else {
        point =
            Utilities::getTopLeftPoint(transforms[i].position, width, height);
      }

      SDL_Rect box = {point.x, point.y, width, height};

      SDL_RenderDrawRect(game.renderer(), &box);
    }
  }
};
