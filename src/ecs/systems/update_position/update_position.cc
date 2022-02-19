#include "update_position.h"

#include "ecs/components/collider.h"
#include "ecs/components/physics.h"
#include "ecs/components/transform.h"
#include "ecs/pools/bullets/bullets.h"

void UpdatePosition::update(Engine& e) {
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
    if (e.isOutOfBounds(collider[id].box)) {
      e.bullets().deactivate(e, id);
    }
  }
}
