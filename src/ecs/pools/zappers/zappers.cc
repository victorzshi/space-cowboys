#include "zappers.h"

#include "ecs/components/collider.h"
#include "ecs/components/physics.h"
#include "ecs/components/sprite.h"
#include "ecs/engine.h"

void Zappers::initialize() {
  Sprite sprite = e_->createSpriteFromFile(TEXTURE_FILE);

  int index = 0;
  for (int i = 0; i < TOTAL; i++) {
    int id = e_->createEntity();

    physics_[id].velocity.y = DELTA_VELOCITY;

    collider_[id].box.w = WIDTH;
    collider_[id].box.h = WIDTH;

    sprite_[id] = sprite;

    index = id;
  }

  begin_ = index - (TOTAL - 1);
  size_ = index - (TOTAL - 1);
  end_ = index;
}
