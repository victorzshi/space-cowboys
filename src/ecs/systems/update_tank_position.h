#pragma once

#include "ecs/ecs.h"

class UpdateTankPosition {
 public:
  static void update(ECS& ecs) {
    Transform* transform = ecs.transform();
    Physics* physics = ecs.physics();

    int id = ecs.tankIds[0];

    physics[id].velocity += physics[id].acceleration;
    physics[id].velocity = physics[id].velocity.limit(3.0f);
    transform[id].position += physics[id].velocity;
    physics[id].updateCollider(transform[id].position);

    if (ecs.isOutOfBounds(physics[id].collider)) {
      transform[id].position -= physics[id].velocity;
      physics[id].updateCollider(transform[id].position);

      physics[id].velocity.x = 0.0f;
      physics[id].acceleration.x = 0.0f;
    }
  }
};
