#pragma once

#include "ecs/ecs.h"

class UpdatePosition {
 public:
  static void update(ECS& ecs) {
    Transform* transform = ecs.transform();
    Physics* physics = ecs.physics();
    Collider* collider = ecs.collider();
    AI* ai = ecs.ai();

    for (int i = 0; i < ecs.size(); i++) {
      physics[i].velocity += physics[i].acceleration;
      transform[i].position += physics[i].velocity;
      collider[i].update(transform[i].position);
    }

    if (ecs.isOutOfBounds()) {
      for (int i = 0; i < ecs.size(); i++) {
        transform[i].position -= physics[i].velocity;
        collider[i].update(transform[i].position);

        if (ai[i].nextDirection == Direction::kLeft ||
            ai[i].nextDirection == Direction::kRight) {
          ai[i].isPathEnd = true;
        }
      }
    }
  }
};
