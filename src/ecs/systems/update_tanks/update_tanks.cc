#include "update_tanks.h"

#include "ecs/components/collider.h"
#include "ecs/components/physics.h"
#include "ecs/components/transform.h"
#include "ecs/engine.h"
#include "ecs/pools/tanks/tanks.h"

void UpdateTanks::update(Engine& e) {
  Collider* collider = e.collider();
  Physics* physics = e.physics();
  Transform* transform = e.transform();

  Tanks& tanks = e.tanks();

  int begin = tanks.begin();
  int size = tanks.size();
  for (int i = begin; i < size; i++) {
    if (e.isOutOfBounds(collider[i].box)) {
      for (int j = begin; j < size; j++) {
        transform[j].position -= physics[j].velocity;
        collider[j].update(transform[j].position);
        physics[j].velocity = Vector2();
      }
    }
  }
}
