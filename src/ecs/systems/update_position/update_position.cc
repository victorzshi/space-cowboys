#include "update_position.h"

#include "ecs/components/ai.h"
#include "ecs/components/collider.h"
#include "ecs/components/physics.h"
#include "ecs/components/transform.h"
#include "ecs/engine.h"
#include "ecs/pools/aliens/aliens.h"
#include "ecs/pools/bullets/bullets.h"

void UpdatePosition::update(Engine& e) {
  updateAliens(e);
  updateBullets(e);
}

void UpdatePosition::updateAliens(Engine& e) {
  AI* ai = e.ai();
  Transform* transform = e.transform();
  Physics* physics = e.physics();
  Collider* collider = e.collider();

  int begin = e.aliens().begin();
  int active = e.aliens().active();

  for (int i = begin; i < active; i++) {
    physics[i].velocity = physics[i].velocity.limit(2.0f);
    transform[i].position += physics[i].velocity;
    collider[i].update(transform[i].position);
  }

  for (int i = begin; i < active; i++) {
    if (e.isOutOfBounds(collider[i].box)) {
      for (int j = begin; j < active; j++) {
        transform[j].position -= physics[j].velocity;
        collider[j].update(transform[j].position);
        ai[j].isPathEnd = true;
      }
      break;
    }
  }
}

void UpdatePosition::updateBullets(Engine& e) {
  Collider* collider = e.collider();
  Transform* transform = e.transform();
  Physics* physics = e.physics();

  int begin = e.bullets().begin();
  int active = e.bullets().active();

  for (int i = begin; i < active; i++) {
    transform[i].position += physics[i].velocity;
    collider[i].update(transform[i].position);
  }

  for (int i = begin; i < e.bullets().active(); i++) {
    if (e.isOutOfBounds(collider[i].box)) {
      e.bullets().deactivate(i);
      continue;
    }

    for (int j = e.aliens().begin(); j < e.aliens().active(); j++) {
      if (collider[i].isHit(collider[j].box)) {
        e.bullets().deactivate(i);
        e.aliens().deactivate(j);
        break;
      }
    }
  }
}
