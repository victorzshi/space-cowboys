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
int Pool::size() { return size_; }
int Pool::end() { return end_; }

bool Pool::activate(int index) {
  assert(index >= size_);

  if (size_ > end_) return false;  // Do not blow memory up

  memorySwap(index);

  size_++;

  return true;
}

bool Pool::deactivate(int index) {
  assert(index < size_);

  size_--;

  memorySwap(index);

  return true;
}

void Pool::memorySwap(int index) {
  if (size_ == index) return;

  AI aiSwap = ai_[size_];
  ai_[size_] = ai_[index];
  ai_[index] = aiSwap;

  Collider colliderSwap = collider_[size_];
  collider_[size_] = collider_[index];
  collider_[index] = colliderSwap;

  Physics physicsSwap = physics_[size_];
  physics_[size_] = physics_[index];
  physics_[index] = physicsSwap;

  Sprite spriteSwap = sprite_[size_];
  sprite_[size_] = sprite_[index];
  sprite_[index] = spriteSwap;

  Transform transformSwap = transform_[size_];
  transform_[size_] = transform_[index];
  transform_[index] = transformSwap;
}
