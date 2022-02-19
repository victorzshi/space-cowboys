#include "ecs.h"

#include <assert.h>

#include "systems/process_input.h"

ECS::ECS() : viewport_({0, 0, 0, 0}), renderer_(nullptr), id_(0) {
  collider_ = new Collider[MAX_ENTITIES];
  physics_ = new Physics[MAX_ENTITIES];
  sprite_ = new Sprite[MAX_ENTITIES];
  transform_ = new Transform[MAX_ENTITIES];
}

void ECS::initialize(SDL_Rect viewport, SDL_Renderer* renderer) {
  viewport_ = viewport;
  renderer_ = renderer;

  bullets.initialize(*this, 5);
}

void ECS::terminate() {
  // Do stuff
}

SDL_Rect& ECS::viewport() { return viewport_; }
SDL_Renderer* ECS::renderer() { return renderer_; }

Collider* ECS::collider() { return collider_; }
Physics* ECS::physics() { return physics_; }
Sprite* ECS::sprite() { return sprite_; }
Transform* ECS::transform() { return transform_; }

int ECS::createEntity() {
  assert(id_ < MAX_ENTITIES);
  id_++;
  return id_ - 1;  // Array index starts at 0
}

void ECS::input() { ProcessInput::input(); }

void ECS::update() {
  // Do nothing
}

void ECS::render(float delay) {
  // Do nothing
  (void)delay;
}
