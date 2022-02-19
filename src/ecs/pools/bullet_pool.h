#pragma once

#include <assert.h>

#include "ecs/components/physics.h"
#include "ecs/components/transform.h"
#include "utils/utils.h"

class BulletPool {
 public:
  BulletPool()
      : physics_(nullptr),
        transform_(nullptr),
        begin_(0),
        active_(0),
        end_(0) {}

  void setPhysics(Physics* physics) { physics_ = physics; }
  void setTransform(Transform* transform) { transform_ = transform; }

  void setBegin(int index) { begin_ = index; }
  void setActive(int index) { active_ = index; }
  void setEnd(int index) { end_ = index; }

  void activate(Vector2 position) {
    if (active_ > end_) return;

    transform_[active_].position = position;

    active_++;
  }

  void deactivate(int id) {
    assert(id < active_);

    active_--;

    // TODO(Victor): Could probably make this a generic function in ECS.
    Physics tempPhysics = physics_[active_];
    physics_[active_] = physics_[id];
    physics_[id] = tempPhysics;

    // TODO(Victor): Could probably make this a generic function in ECS.
    Transform tempTransform = transform_[active_];
    transform_[active_] = transform_[id];
    transform_[id] = tempTransform;
  }

  // TODO(Victor): This is a system.
  void update() {
    for (int id = begin_; id < active_; id++) {
      transform_[id].position += physics_[id].velocity;
      physics_[id].updateCollider(transform_[id].position);
    }

    for (int id = begin_; id < active_; id++) {
      if (isOutOfBounds(physics_[id].collider)) {
        deactivate(id);
      }
    }
  }

  // TODO(Victor): This is a system.
  void render(SDL_Renderer* renderer) {
    for (int id = begin_; id < active_; id++) {
      SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
      SDL_RenderDrawRect(renderer, &physics_[id].collider);
    }
  }

 private:
  Physics* physics_;
  Transform* transform_;

  int begin_;
  int active_;
  int end_;

  // TODO(Victor): This is for the system.
  bool isOutOfBounds(SDL_Rect rect) {
    int topLeftX = rect.x;
    int topLeftY = rect.y;
    int bottomRightX = rect.x + rect.w;
    int bottomRightY = rect.y + rect.h;

    return topLeftX < 0 || topLeftY < 0 || bottomRightX > 1280 ||
           bottomRightY > 720;
  }
};
