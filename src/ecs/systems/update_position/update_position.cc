#include "update_position.h"

#include "ecs/components/ai.h"
#include "ecs/components/collider.h"
#include "ecs/components/physics.h"
#include "ecs/components/transform.h"
#include "ecs/engine.h"
#include "ecs/pools/aliens/aliens.h"
#include "ecs/pools/bullets/bullets.h"

void UpdatePosition::update(Engine& e) {
  updateActive(e, e.aliens());
  updateActive(e, e.bullets());
  updateAliensPath(e);
  resolveBulletHit(e);
}

void UpdatePosition::updateActive(Engine& e, Pool& pool) {
  Transform* transform = e.transform();
  Physics* physics = e.physics();
  Collider* collider = e.collider();

  int begin = pool.begin();
  int size = pool.size();

  for (int i = begin; i < size; i++) {
    transform[i].position += physics[i].velocity;
    collider[i].update(transform[i].position);
  }
}

void UpdatePosition::updateAliensPath(Engine& e) {
  AI* ai = e.ai();
  Transform* transform = e.transform();
  Physics* physics = e.physics();
  Collider* collider = e.collider();

  int begin = e.aliens().begin();
  int size = e.aliens().size();

  for (int i = begin; i < size; i++) {
    if (e.isOutOfBounds(collider[i].box)) {
      for (int j = begin; j < size; j++) {
        transform[j].position -= physics[j].velocity;
        collider[j].update(transform[j].position);
        ai[j].isPathEnd = true;
      }
      break;
    }
  }
}

void UpdatePosition::resolveBulletHit(Engine& e) {
  Collider* collider = e.collider();

  Bullets& bullets = e.bullets();
  Aliens& aliens = e.aliens();

  int beginBullets = bullets.begin();
  int beginAliens = aliens.begin();

  for (int i = beginBullets; i < bullets.size(); i++) {
    if (e.isOutOfBounds(collider[i].box)) {
      bullets.deactivate(i);
      continue;
    }

    for (int j = beginAliens; j < aliens.size(); j++) {
      if (collider[i].isHit(collider[j].box)) {
        bullets.deactivate(i);
        aliens.deactivate(j);
        break;
      }
    }
  }
}
