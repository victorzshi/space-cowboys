#include "explosions.h"

#include "ecs/components/sprite.h"
#include "ecs/engine.h"
#include "services/locator.h"

void Explosions::initialize() {
  Locator::logger().print("Initializing explosions...");

  SDL_Texture* texture = e_->createTexture(TEXTURE_FILE);

  int index = 0;
  for (int i = 0; i < TOTAL; i++) {
    int id = e_->createEntity();

    sprite_[id].texture = texture;

    index = id;
  }

  begin_ = index - (TOTAL - 1);
  size_ = index - (TOTAL - 1);
  end_ = index;
}
