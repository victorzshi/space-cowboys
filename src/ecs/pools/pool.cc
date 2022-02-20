#include "pool.h"

#include <assert.h>

#include "ecs/components/ai.h"
#include "ecs/components/collider.h"
#include "ecs/components/physics.h"
#include "ecs/components/sprite.h"
#include "ecs/components/transform.h"
#include "ecs/engine.h"

Pool::Pool() {}

int Pool::begin() { return begin_; }
int Pool::active() { return active_; }
int Pool::end() { return end_; }

void Pool::activate(Engine& e, int index) {
  assert(index >= active_);

  // Do not blow memory up
  if (active_ > end_) return;

  swapMemory(e, active_, index);

  active_++;
}

void Pool::deactivate(Engine& e, int index) {
  assert(index < active_);

  active_--;

  swapMemory(e, active_, index);
}

void Pool::swapMemory(Engine& e, int i, int j) {
  AI* ai = e.ai();
  Collider* collider = e.collider();
  Physics* physics = e.physics();
  Sprite* sprite = e.sprite();
  Transform* transform = e.transform();

  AI aiTemp = ai[i];
  ai[i] = ai[j];
  ai[j] = aiTemp;

  Collider colliderTemp = collider[i];
  collider[i] = collider[j];
  collider[j] = colliderTemp;

  Physics physicsTemp = physics[i];
  physics[i] = physics[j];
  physics[j] = physicsTemp;

  Sprite spriteTemp = sprite[i];
  sprite[i] = sprite[j];
  sprite[j] = spriteTemp;

  Transform transformTemp = transform[i];
  transform[i] = transform[j];
  transform[j] = transformTemp;
}
