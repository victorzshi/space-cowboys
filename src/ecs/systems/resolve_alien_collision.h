#pragma once

#include "ecs/ecs.h"

class ResolveAlienCollision {
 public:
  static void update(ECS& ecs) {
    Transform* transform = ecs.transform();

    for (size_t i = 0; i < ecs.alienIds.size(); i++) {
      int id = ecs.alienIds[i];

      if (ecs.isOutOfBounds(transform[id].position)) {
        shiftAliens(ecs);
        break;
      }
    }
  }

 private:
  static void shiftAliens(ECS& ecs) {
    Transform* transform = ecs.transform();
    Physics* physics = ecs.physics();
    Collider* collider = ecs.collider();
    AI* ai = ecs.ai();

    for (size_t i = 0; i < ecs.alienIds.size(); i++) {
      int id = ecs.alienIds[i];

      transform[id].position -= physics[id].velocity;
      collider[id].update(transform[id].position);
      ai[id].isPathEnd = true;
    }
  }
};
