#pragma once

#include "ecs/ecs.h"

class ResolveBulletHit {
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

          increaseAlienSpeed(ecs);

          break;
        }
      }

      if (active[bullet].isNotActive()) continue;

      for (size_t k = 0; k < ecs.wallIds.size(); k++) {
        int wall = ecs.wallIds[k];

        if (active[wall].isNotActive()) continue;

        if (physics[bullet].isCollision(physics[wall].collider)) {
          active[bullet].state = false;
          active[wall].state = false;

          break;
        }
      }
    }
  }

 private:
  static void increaseAlienSpeed(ECS& ecs) {
    Active* active = ecs.active;
    Physics* physics = ecs.physics;

    for (size_t i = 0; i < ecs.alienIds.size(); i++) {
      int id = ecs.alienIds[i];

      if (active[id].isNotActive()) continue;

      physics[id].deltaVelocity += physics[id].deltaVelocity * 0.05f;
    }
  }
};
