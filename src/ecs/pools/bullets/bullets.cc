#include "bullets.h"

#include <assert.h>

#include "ecs/components/collider.h"
#include "ecs/components/physics.h"
#include "ecs/components/sprite.h"
#include "ecs/components/transform.h"
#include "services/locator.h"
#include "utils/utils.h"

Bullets::Bullets() : begin_(0), active_(0), end_(0) {}

void Bullets::initialize(ECSInterface& ecs, int total) {
  Locator::logger().print("Initializing bullets...");

  int width = 18;
  float deltaVelocity = 5.0f;
  SDL_Texture* texture =
      Utils::createTexture(ecs.renderer(), "../../data/images/tank-bullet.png");

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

int Bullets::begin() { return begin_; }
int Bullets::active() { return active_; }
int Bullets::end() { return end_; }

void Bullets::activate(ECSInterface& ecs, int id) {
  Locator::logger().print("Activating bullet...");
  Locator::logger().print(std::to_string(id));

  if (active_ > end_) return;

  Transform* transform = ecs.transform();

  // TODO(Victor): Set to tank position
  transform[active_].position = Vector2(500.0f, 500.0f);

  Transform temp = transform[active_];
  transform[active_] = transform[id];
  transform[id] = temp;

  active_++;
}

void Bullets::deactivate(ECSInterface& ecs, int id) {
  Locator::logger().print("Deactivating bullet...");
  Locator::logger().print(std::to_string(id));

  assert(id < active_);

  Transform* transform = ecs.transform();

  active_--;

  // TODO(Victor): Could probably make this a generic function in ECS.
  Transform temp = transform[active_];
  transform[active_] = transform[id];
  transform[id] = temp;
}
