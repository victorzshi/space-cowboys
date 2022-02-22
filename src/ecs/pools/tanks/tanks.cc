#include "tanks.h"

#include <assert.h>

#include "ecs/components/collider.h"
#include "ecs/components/physics.h"
#include "ecs/components/sprite.h"
#include "ecs/components/timer.h"
#include "ecs/components/transform.h"
#include "ecs/engine.h"

void Tanks::initialize() {
  Sprite sprite = e_->createSpriteFromFile(TEXTURE_FILE);

  Uint64 previous = SDL_GetTicks64();

  int index = 0;
  for (int i = 0; i < TOTAL; i++) {
    int id = e_->createEntity();

    int offsetX = -(TOTAL * WIDTH / 2) + (WIDTH / 2);
    float x = static_cast<float>(e_->viewport().w / 2 + offsetX);
    float y = static_cast<float>(e_->viewport().h - WIDTH / 2);

    transform_[id].position.x = x + static_cast<float>(i * WIDTH);
    transform_[id].position.y = y;

    collider_[id].box.w = WIDTH;
    collider_[id].box.h = WIDTH;

    sprite_[id] = sprite;

    timer_[id].previous = previous;

    index = id;
  }

  begin_ = index - (TOTAL - 1);
  size_ = index + 1;
  end_ = index;
}
