#include "particles.h"

#include <SDL.h>

#include "ecs/components/collider.h"
#include "ecs/components/physics.h"
#include "ecs/components/sprite.h"
#include "ecs/engine.h"
#include "services/locator.h"

void Particles::initialize() {
  Locator::logger().print("Initializing particles...");

  SDL_Texture* texture = e_->createTexture(TEXTURE_FILE);

  int index = 0;
  for (int i = 0; i < TOTAL; i++) {
    int id = e_->createEntity();

    collider_[id].box.w = WIDTH;
    collider_[id].box.h = WIDTH;

    sprite_[id].texture = texture;

    index = id;
  }

  begin_ = index - (TOTAL - 1);
  size_ = index - (TOTAL - 1);
  end_ = index;
}
