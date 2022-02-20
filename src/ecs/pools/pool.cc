#include "pool.h"

#include <assert.h>

#include "ecs/components/ai.h"
#include "ecs/components/collider.h"
#include "ecs/components/physics.h"
#include "ecs/components/sprite.h"
#include "ecs/components/transform.h"
#include "ecs/engine.h"

Pool::Pool()
    : e_(nullptr),
      ai_(nullptr),
      collider_(nullptr),
      physics_(nullptr),
      sprite_(nullptr),
      transform_(nullptr) {}

void Pool::setEngine(Engine* e) {
  e_ = e;
  ai_ = e->ai();
  collider_ = e->collider();
  physics_ = e->physics();
  sprite_ = e->sprite();
  transform_ = e->transform();
}

int Pool::begin() { return begin_; }
int Pool::active() { return active_; }
int Pool::end() { return end_; }

void Pool::activate(int index) {
  assert(index >= active_);

  if (active_ > end_) return;  // Do not blow memory up

  memorySwap(index);

  active_++;
}

void Pool::deactivate(int index) {
  assert(index < active_);

  active_--;

  memorySwap(index);
}

void Pool::memorySwap(int index) {
  AI aiSwap = ai_[active_];
  ai_[active_] = ai_[index];
  ai_[index] = aiSwap;

  Collider colliderSwap = collider_[active_];
  collider_[active_] = collider_[index];
  collider_[index] = colliderSwap;

  Physics physicsSwap = physics_[active_];
  physics_[active_] = physics_[index];
  physics_[index] = physicsSwap;

  Sprite spriteSwap = sprite_[active_];
  sprite_[active_] = sprite_[index];
  sprite_[index] = spriteSwap;

  Transform transformSwap = transform_[active_];
  transform_[active_] = transform_[index];
  transform_[index] = transformSwap;
}
