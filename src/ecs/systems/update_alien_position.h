#pragma once

#include "ecs/ecs.h"

class UpdateAlienPosition {
 public:
  static void update(ECS& ecs) {
    Active* active = ecs.active;
    Transform* transform = ecs.transform;
    Physics* physics = ecs.physics;

    for (size_t i = 0; i < ecs.alienIds.size(); i++) {
      int id = ecs.alienIds[i];

      if (active[id].isNotActive()) continue;

      physics[id].velocity = physics[id].velocity.limit(2.0f);
      transform[id].position += physics[id].velocity;
      physics[id].updateCollider(transform[id].position);
    }

    for (size_t i = 0; i < ecs.alienIds.size(); i++) {
      int id = ecs.alienIds[i];

      if (active[id].isNotActive()) continue;

      if (ecs.isOutOfBounds(physics[id].collider)) {
        shiftAllAliens(ecs);

        break;
      }
    }
  }

 private:
  static void shiftAllAliens(ECS& ecs) {
    Active* active = ecs.active;
    Transform* transform = ecs.transform;
    Physics* physics = ecs.physics;
    AI* ai = ecs.ai;

    for (size_t i = 0; i < ecs.alienIds.size(); i++) {
      int id = ecs.alienIds[i];

      if (active[id].isNotActive()) continue;

      transform[id].position -= physics[id].velocity;
      physics[id].updateCollider(transform[id].position);
      ai[id].isPathEnd = true;
    }
  }
};
