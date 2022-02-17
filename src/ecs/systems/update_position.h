#pragma once

#include "ecs/ecs.h"

class UpdatePosition {
 public:
  static void update(ECS& ecs) {
    Transform* transform = ecs.transform();
    Physics* physics = ecs.physics();
    Collider* collider = ecs.collider();

    for (size_t i = 0; i < ecs.allIds.size(); i++) {
      int id = ecs.allIds[i];

      physics[id].velocity += physics[id].acceleration;
      transform[id].position += physics[id].velocity;
      collider[id].update(transform[id].position);
    }
  }
};
