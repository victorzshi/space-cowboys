#include "bullets.h"

#include <assert.h>

#include "ecs/components/collider.h"
#include "ecs/components/physics.h"
#include "ecs/components/sprite.h"
#include "ecs/components/transform.h"
#include "ecs/engine.h"
#include "services/locator.h"

Bullets::Bullets() {}

void Bullets::initialize() {
  Locator::logger().print("Initializing bullets...");
  int total = 50;
  int width = 18;
  float deltaVelocity = 5.0f;
  SDL_Texture* texture = e_->createTexture("tank-bullet.png");

  int index = 0;
  for (int i = 0; i < total; i++) {
    int id = e_->createEntity();

    physics_[id].velocity.y = -deltaVelocity;

    collider_[id].box.w = width;
    collider_[id].box.h = width;

    sprite_[id].texture = texture;

    index = id;
  }

  begin_ = index - (total - 1);
  active_ = index - (total - 1);
  end_ = index;
}
