#pragma once

#include "ecs/engine.h"
#include "utils/utils.h"

class UpdatePosition {
 public:
  static void update(Engine& e) {
    Transform* transform = e.transform();
    Physics* physics = e.physics();
    Collider* collider = e.collider();

    int begin = e.bullets().begin();
    int active = e.bullets().active();

    for (int id = begin; id < active; id++) {
      transform[id].position += physics[id].velocity;
      collider[id].update(transform[id].position);
    }

    for (int id = begin; id < e.bullets().active(); id++) {
      if (Utils::isOutOfBounds(collider[id].box)) {
        e.bullets().deactivate(e, id);
      }
    }
  }
};
