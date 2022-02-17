#pragma once

#include "ecs/ecs.h"

class ResolveBulletCollision {
 public:
  static void update(ECS& ecs) {
    Active* active = ecs.active;
    Physics* physics = ecs.physics;

    for (size_t i = 0; i < ecs.bulletIds.size(); i++) {
      int bullet = ecs.bulletIds[i];

      if (active[bullet].isNotActive()) continue;

      for (size_t j = 0; j < ecs.alienIds.size(); j++) {
        int alien = ecs.alienIds[j];

        if (active[alien].isNotActive()) continue;

        if (physics[bullet].isCollision(physics[alien].collider)) {
          active[bullet].state = false;
          active[alien].state = false;
          break;
        }
      }
    }
  }
};
