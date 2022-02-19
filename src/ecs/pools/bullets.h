#pragma once

#include <assert.h>

#include "ecs/ecs_interface.h"
#include "utils/utils.h"

class Bullets {
 public:
  Bullets() : begin_(0), active_(0), end_(0) {}

  void initialize(ECSInterface& ecs, int total) {
    int width = 18;
    float deltaVelocity = 5.0f;
    SDL_Texture* texture = Utils::createTexture(
        ecs.renderer(), "../../data/images/tank-bullet.png");

    Physics* physics = ecs.physics();
    Collider* collider = ecs.collider();
    Sprite* sprite = ecs.sprite();

    int index = 0;
    for (int i = 0; i < total; i++) {
      int id = ecs.createEntity();

      physics[id].velocity.y = -deltaVelocity;

      collider[id].box.w = width;
      collider[id].box.h = width;

      sprite[id].texture = texture;

      index = id;
    }

    begin_ = index - (total - 1);
    active_ = index - (total - 1);
    end_ = index;
  }

  void activate(ECSInterface& ecs) {
    if (active_ > end_) return;

    Transform* transform = ecs.transform();

    // Set to tank position
    transform[active_].position = Vector2(10.0f, 10.0f);

    active_++;
  }

  void deactivate(ECSInterface& ecs, int id) {
    assert(id < active_);

    Transform* transform = ecs.transform();

    active_--;

    // TODO(Victor): Could probably make this a generic function in ECS.
    // Also, for this object, don't even need to swap...
    Transform temp = transform[active_];
    transform[active_] = transform[id];
    transform[id] = temp;
  }

 private:
  int begin_;
  int active_;
  int end_;
};
