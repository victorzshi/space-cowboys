#pragma once

#include "ecs/ecs.h"

class UpdateBulletPosition {
 public:
  static void update(ECS& ecs) {
    Active* active = ecs.active;
    Transform* transform = ecs.transform;
    Physics* physics = ecs.physics;

    for (size_t i = 0; i < ecs.bulletIds.size(); i++) {
      int id = ecs.bulletIds[i];

      if (active[id].isActive()) {
        transform[id].position += physics[id].velocity;
        physics[id].updateCollider(transform[id].position);
      }
    }

    for (size_t i = 0; i < ecs.bulletIds.size(); i++) {
      int id = ecs.bulletIds[i];

      if (ecs.isOutOfBounds(physics[id].collider)) {
        active[id].state = false;
      }
    }
  }
};
