#include "explosions.h"

#include "ecs/components/sprite.h"
#include "ecs/engine.h"

void Explosions::initialize() {
  Sprite sprite = e_->createSpriteFromFile(TEXTURE_FILE);

  int index = 0;
  for (int i = 0; i < TOTAL; i++) {
    int id = e_->createEntity();

    sprite_[id] = sprite;

    index = id;
  }

  begin_ = index - (TOTAL - 1);
  size_ = index - (TOTAL - 1);
  end_ = index;
}
