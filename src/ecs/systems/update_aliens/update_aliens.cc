#include "update_aliens.h"

#include "ecs/components/ai.h"
#include "ecs/components/collider.h"
#include "ecs/components/physics.h"
#include "ecs/components/transform.h"
#include "ecs/engine.h"
#include "ecs/pools/aliens/aliens.h"

void UpdateAliens::update(Engine& e) {
  AI* ai = e.ai();
  Collider* collider = e.collider();
  Physics* physics = e.physics();
  Transform* transform = e.transform();

  Aliens& aliens = e.aliens();

  int begin = aliens.begin();
  int size = aliens.size();

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
