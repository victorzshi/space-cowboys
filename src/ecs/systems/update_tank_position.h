#pragma once

#include "ecs/ecs.h"

class UpdateTankPosition {
 public:
  static void update(ECS& ecs) {
    Transform* transform = ecs.transform();
    Physics* physics = ecs.physics();
    Collider* collider = ecs.collider();

    int id = ecs.tankIds[0];

    physics[id].velocity += physics[id].acceleration;
    physics[id].velocity = physics[id].velocity.limit(3.0f);
    transform[id].position += physics[id].velocity;

    if (ecs.isOutOfBounds(collider[id].rect)) {
      transform[id].position -= physics[id].velocity;

      physics[id].velocity = Vector2();
      physics[id].acceleration = Vector2();
    }

    collider[id].update(transform[id].position);
  }
};
