#pragma once

#include "ecs/ecs_interface.h"
#include "utils/utils.h"

class UpdatePosition {
 public:
  static void update(ECSInterface& ecs) {
    Transform* transform = ecs.transform();
    Physics* physics = ecs.physics();
    Collider* collider = ecs.collider();

    int begin = ecs.bullets().begin();
    int active = ecs.bullets().active();

    for (int id = begin; id < active; id++) {
      transform[id].position += physics[id].velocity;
      collider[id].update(transform[id].position);
    }

    for (int id = begin; id < ecs.bullets().active(); id++) {
      if (Utils::isOutOfBounds(collider[id].box)) {
        ecs.bullets().deactivate(ecs, id);
      }
    }
  }
};
