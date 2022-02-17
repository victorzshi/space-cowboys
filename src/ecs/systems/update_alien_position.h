#pragma once

#include "ecs/ecs.h"

class UpdateAlienPosition {
 public:
  static void update(ECS& ecs) {
    Transform* transform = ecs.transform();
    Physics* physics = ecs.physics();
    Collider* collider = ecs.collider();

    for (size_t i = 0; i < ecs.alienIds.size(); i++) {
      int id = ecs.alienIds[i];

      transform[id].position += physics[id].velocity;
      collider[id].update(transform[id].position);
    }

    for (size_t i = 0; i < ecs.alienIds.size(); i++) {
      int id = ecs.alienIds[i];

      if (ecs.isOutOfBounds(collider[id].rect)) {
        shiftAllAliens(ecs);
        break;
      }
    }
  }

 private:
  static void shiftAllAliens(ECS& ecs) {
    Transform* transform = ecs.transform();
    Physics* physics = ecs.physics();
    Collider* collider = ecs.collider();
    AI* ai = ecs.ai();

    for (size_t j = 0; j < ecs.alienIds.size(); j++) {
      int id = ecs.alienIds[j];

      transform[id].position -= physics[id].velocity;
      collider[id].update(transform[id].position);
      ai[id].isPathEnd = true;
    }
  }
};
