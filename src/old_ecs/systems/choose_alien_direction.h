#pragma once

#include "ecs/ecs.h"

class ChooseAlienDirection {
 public:
  static void update(ECS& ecs) {
    // TODO(Victor): State machine would be better suited for this logic.

    Active* active = ecs.active;
    AI* ai = ecs.ai;
    Transform* transform = ecs.transform;
    Physics* physics = ecs.physics;

    for (size_t i = 0; i < ecs.alienIds.size(); i++) {
      int id = ecs.alienIds[i];

      if (active[id].isNotActive()) continue;

      if (ai[id].isPathEnd) {
        ai[id].isPathEnd = false;

        ai[id].prevDirection = ai[id].nextDirection;
        ai[id].nextDirection = Direction::kDown;

        ai[id].goalHeight += static_cast<float>(physics[id].collider.h);
      }

      if (ai[id].nextDirection == Direction::kDown &&
          transform[id].position.y >= ai[id].goalHeight) {
        ai[id].nextDirection = ai[id].prevDirection == Direction::kLeft
                                   ? Direction::kRight
                                   : Direction::kLeft;
        ai[id].prevDirection = Direction::kDown;
      }

      switch (ai[id].nextDirection) {
        case Direction::kLeft:
          physics[id].velocity.x = -physics[id].deltaVelocity;
          physics[id].velocity.y = 0.0f;
          break;
        case Direction::kRight:
          physics[id].velocity.x = physics[id].deltaVelocity;
          physics[id].velocity.y = 0.0f;
          break;
        case Direction::kDown:
          physics[id].velocity.x = 0.0f;
          physics[id].velocity.y = physics[id].deltaVelocity;
          break;
      }
    }
  }
};