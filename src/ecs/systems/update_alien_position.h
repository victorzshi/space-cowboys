#pragma once

#include "ecs/ecs.h"

class UpdateAlienPosition {
 public:
  static void update(ECS& ecs) {
    Transform* transform = ecs.transform();
    Physics* physics = ecs.physics();

    for (size_t i = 0; i < ecs.alienIds.size(); i++) {
      int id = ecs.alienIds[i];

      transform[id].position += physics[id].velocity;
      physics[id].updateCollider(transform[id].position);
    }

    for (size_t i = 0; i < ecs.alienIds.size(); i++) {
      int id = ecs.alienIds[i];

      if (ecs.isOutOfBounds(physics[id].collider)) {
        shiftAllAliens(ecs);
        break;
      }
    }
  }

 private:
  static void shiftAllAliens(ECS& ecs) {
    Transform* transform = ecs.transform();
    Physics* physics = ecs.physics();
    AI* ai = ecs.ai();

    for (size_t j = 0; j < ecs.alienIds.size(); j++) {
      int id = ecs.alienIds[j];

      transform[id].position -= physics[id].velocity;
      physics[id].updateCollider(transform[id].position);
      ai[id].isPathEnd = true;
    }
  }
};
