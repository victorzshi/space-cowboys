#pragma once

#include "ecs/ecs.h"

class ChooseAlienDirection {
 public:
  static void update(ECS& ecs) {
    // TODO(Victor): State machine would be better suited for this logic.

    AI* ai = ecs.ai();
    Transform* transform = ecs.transform();
    Physics* physics = ecs.physics();
    Collider* collider = ecs.collider();

    for (int i = 0; i < ecs.size(); i++) {
      if (ai[i].isPathEnd) {
        ai[i].isPathEnd = false;

        ai[i].prevDirection = ai[i].nextDirection;
        ai[i].nextDirection = Direction::kDown;

        ai[i].goalHeight += static_cast<float>(collider[i].rect.h);
      }

      if (ai[i].nextDirection == Direction::kDown &&
          transform[i].position.y >= ai[i].goalHeight) {
        ai[i].nextDirection = ai[i].prevDirection == Direction::kLeft
                                  ? Direction::kRight
                                  : Direction::kLeft;
        ai[i].prevDirection = Direction::kDown;
      }

      switch (ai[i].nextDirection) {
        case Direction::kLeft:
          physics[i].velocity.x = -physics[i].speed;
          physics[i].velocity.y = 0.0f;
          break;
        case Direction::kRight:
          physics[i].velocity.x = physics[i].speed;
          physics[i].velocity.y = 0.0f;
          break;
        case Direction::kDown:
          physics[i].velocity.x = 0.0f;
          physics[i].velocity.y = physics[i].speed;
          break;
        case Direction::kNone:
          break;
      }
    }
  }
};
