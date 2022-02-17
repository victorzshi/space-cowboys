#pragma once

#include "ecs/ecs.h"

class CheckBulletHit {
 public:
  static void update(ECS& ecs) {
    Physics* physics = ecs.physics();

    for (size_t i = 0; i < ecs.bulletIds.size(); i++) {
      int bullet = ecs.bulletIds[i];

      if (!physics[bullet].isActive) continue;

      for (size_t j = 0; j < ecs.alienIds.size(); j++) {
        int alien = ecs.alienIds[j];

        if (physics[bullet].isCollision(physics[alien].collider)) {
          physics[bullet].isActive = false;
        }
      }
    }
  }
};
