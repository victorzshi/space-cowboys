#pragma once

#include "ecs/ecs.h"

class UpdateBulletPosition {
 public:
  static void update(ECS& ecs) {
    Transform* transform = ecs.transform();
    Physics* physics = ecs.physics();

    for (size_t i = 0; i < ecs.bulletIds.size(); i++) {
      int id = ecs.bulletIds[i];

      if (physics[id].isActive) {
        transform[id].position += physics[id].velocity;
        physics[id].updateCollider(transform[id].position);
      }
    }

    for (size_t i = 0; i < ecs.bulletIds.size(); i++) {
      int id = ecs.bulletIds[i];

      if (ecs.isOutOfBounds(physics[id].collider)) {
        physics[id].isActive = false;
        physics[id].velocity.y = 0.0f;
      }
    }
  }
};
