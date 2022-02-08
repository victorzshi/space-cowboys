#pragma once

#include "game_object/game_object.h"

class TankUpdateComponent : public UpdateComponent {
 public:
  virtual void update(GameObject& object, Game& game) override {
    (void)game;

    object.velocity = Vector2::add(object.velocity, object.acceleration);

    object.position = Vector2::add(object.position, object.velocity);
  }
};
