#include "entities.h"

#include <assert.h>

#include "systems/square.h"

Entities::Entities() : size_(0) {}

void Entities::initialize(int screenWidth, int screenHeight) {
  transforms = new Transform[kMaxSize];
  physics = new Physics[kMaxSize];

  int entity = createEntity();
  addTransform(entity, {Vec2(20.0, 20.0)});

  entity = createEntity();
  addTransform(entity, {Vec2(20.0, screenHeight - 20.0)});

  entity = createEntity();
  addTransform(entity, {Vec2(screenWidth - 20.0, 20.0)});

  entity = createEntity();
  addTransform(entity, {Vec2(screenWidth - 20.0, screenHeight - 20.0)});
}

int Entities::size() { return size_; }

void Entities::input(SDL_Event event) { Square::inputPositions(*this, event); }

void Entities::update() { Square::updatePositions(*this); }

void Entities::render(SDL_Renderer* renderer, double delay) {
  Square::renderPositions(*this, renderer, delay);
}

int Entities::createEntity() {
  assert(size_ < kMaxSize);

  ++size_;
  return size_ - 1;
}

void Entities::addTransform(int entity, Transform transform) {
  transforms[entity] = transform;
}
