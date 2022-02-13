#pragma once

#include "entities/entities.h"

class UpdatePosition {
 public:
  static void update(Entities& entities) {
    Physics* physics = entities.physics();
    Transform* transforms = entities.transforms();

    for (int i = 0; i < entities.size(); i++) {
      physics[i].velocity =
          Vec2::add(physics[i].velocity, physics[i].acceleration);

      transforms[i].position =
          Vec2::add(transforms[i].position, physics[i].velocity);

      if (transforms[i].position.y > 1080) {
        transforms[i].position.y = 0;
      } else if (transforms[i].position.y < 0) {
        transforms[i].position.y = 1080;
      }
    }
  }
};
