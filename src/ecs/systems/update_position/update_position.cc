#include "update_position.h"

#include "ecs/components/ai.h"
#include "ecs/components/collider.h"
#include "ecs/components/physics.h"
#include "ecs/components/transform.h"
#include "ecs/engine.h"
#include "ecs/pools/aliens/aliens.h"
#include "ecs/pools/bullets/bullets.h"

void UpdatePosition::update(Engine& e) {
  Transform* transform = e.transform();
  Physics* physics = e.physics();
  Collider* collider = e.collider();

  Active active = e.active();

  for (int i = 0; i < active.size; i++) {
    int id = active.ids[i];

    physics[id].velocity += physics[id].acceleration;
    transform[id].position += physics[id].velocity;
    collider[id].update(transform[id].position);
  }
}
