#include "update_position.h"

#include "ecs/components/collider.h"
#include "ecs/components/physics.h"
#include "ecs/components/transform.h"
#include "ecs/engine.h"

void UpdatePosition::update(Engine& e) {
  Collider* collider = e.collider();
  Physics* physics = e.physics();
  Transform* transform = e.transform();

  Active active = e.active();

  for (int i = 0; i < active.size; i++) {
    int id = active.ids[i];

    physics[id].velocity += physics[id].acceleration;
    transform[id].position += physics[id].velocity;
    collider[id].update(transform[id].position);
    physics[id].acceleration = Vector2();
  }
}
