#include "ecs.h"

#include <assert.h>

#include "systems/square.h"

ECS::ECS() : totalEntities_(0) {
  transforms = new Transform[kMaxEntities];

  int entity = createEntity();
  addTransform(entity, {Vector2(10.0, 10.0)});

  entity = createEntity();
  addTransform(entity, {Vector2(20.0, 10.0)});

  entity = createEntity();
  addTransform(entity, {Vector2(50.0, 50.0)});

  entity = createEntity();
  addTransform(entity, {Vector2(200.0, 200.0)});
}

void ECS::input(SDL_Event event) { (void)event; }

void ECS::update() { Square::updatePositions(totalEntities_, transforms); }

void ECS::render(SDL_Renderer* renderer, double delay) {
  (void)delay;
  Square::renderPositions(renderer, totalEntities_, transforms);
}

int ECS::createEntity() {
  assert(totalEntities_ < kMaxEntities);

  ++totalEntities_;
  return totalEntities_ - 1;
}

void ECS::addTransform(int entity, Transform transform) {
  transforms[entity] = transform;
}
