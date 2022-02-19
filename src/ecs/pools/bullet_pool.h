#pragma once

#include <assert.h>

#include "ecs/components/physics.h"
#include "ecs/components/transform.h"

class BulletPool {
 public:
  BulletPool()
      : physics(nullptr), transform(nullptr), begin_(0), active_(0), end_(0) {}

  void setBegin(int index) { begin_ = index; }
  void setActive(int index) { active_ = index; }
  void setEnd(int index) { end_ = index; }

  int begin() { return begin_; }
  int active() { return active_; }
  int end() { return end_; }

  Physics* physics;
  Transform* transform;

  void activate(Vector2 position) {
    if (active_ > end_) return;

    transform[active_].position = position;

    active_++;
  }

  void deactivate(int id) {
    assert(id < active_);

    active_--;

    // TODO(Victor): Could probably make this a generic function in ECS.
    Physics tempPhysics = physics[active_];
    physics[active_] = physics[id];
    physics[id] = tempPhysics;

    // TODO(Victor): Could probably make this a generic function in ECS.
    Transform tempTransform = transform[active_];
    transform[active_] = transform[id];
    transform[id] = tempTransform;
  }

  // TODO(Victor): This is a system.
  void update() {
    for (int id = begin_; id < active_; id++) {
      transform[id].position += physics[id].velocity;
      physics[id].updateCollider(transform[id].position);
    }

    for (int id = begin_; id < active_; id++) {
      if (isOutOfBounds(physics[id].collider)) {
        deactivate(id);
      }
    }
  }

  // TODO(Victor): This is a system.
  void render(SDL_Renderer* renderer) {
    for (int id = begin_; id < active_; id++) {
      SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
      SDL_RenderDrawRect(renderer, &physics[id].collider);
    }
  }

 private:
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
