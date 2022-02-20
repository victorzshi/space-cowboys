#include "bullets.h"

#include <assert.h>

#include "ecs/components/collider.h"
#include "ecs/components/physics.h"
#include "ecs/components/sprite.h"
#include "ecs/components/transform.h"
#include "ecs/engine.h"
#include "services/locator.h"

Bullets::Bullets() {}

void Bullets::initialize(Engine& e) {
  Locator::logger().print("Initializing bullets...");
  int total = 50;
  int width = 18;
  float deltaVelocity = 5.0f;
  SDL_Texture* texture = e.createTexture("tank-bullet.png");

  Physics* physics = e.physics();
  Collider* collider = e.collider();
  Sprite* sprite = e.sprite();

  int index = 0;
  for (int i = 0; i < total; i++) {
    int id = e.createEntity();

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
