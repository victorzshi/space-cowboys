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

  updateAliensPath(e);
}

// TODO(Victor): This should be its own system.
void UpdatePosition::updateAliensPath(Engine& e) {
  AI* ai = e.ai();
  Transform* transform = e.transform();
  Physics* physics = e.physics();
  Collider* collider = e.collider();

  int begin = e.aliens().begin();
  int size = e.aliens().size();

  for (int i = begin; i < size; i++) {
    if (e.isOutOfBoundsWidth(collider[i].box)) {
      for (int j = begin; j < size; j++) {
        transform[j].position -= physics[j].velocity;
        collider[j].update(transform[j].position);
        ai[j].isPathEnd = true;
      }
      break;
    }
  }
}
