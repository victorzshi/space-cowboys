#include "tanks.h"

#include <assert.h>

#include "ecs/components/collider.h"
#include "ecs/components/physics.h"
#include "ecs/components/sprite.h"
#include "ecs/components/transform.h"
#include "ecs/engine.h"
#include "services/locator.h"

void Tanks::initialize() {
  Locator::logger().print("Initializing tanks...");

  SDL_Texture* texture = e_->createTexture(TEXTURE_FILE);

  int index = 0;
  for (int i = 0; i < TOTAL; i++) {
    int id = e_->createEntity();

    float x = static_cast<float>(e_->viewport().w / 2);
    float y = static_cast<float>(e_->viewport().h - 100);
    
    // TODO(Victor): Fix hacky way to spawn more tanks.
    transform_[id].position.x = x + static_cast<float>(i) * 100.0f;
    transform_[id].position.y = y;

    collider_[id].box.w = WIDTH;
    collider_[id].box.h = WIDTH;

    sprite_[id].texture = texture;

    index = id;
  }

  begin_ = index - (TOTAL - 1);
  size_ = index + 1;
  end_ = index;
}
