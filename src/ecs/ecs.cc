#include "ecs.h"

#include <assert.h>

#include "systems/process_input.h"

ECS::ECS() : viewport_({0, 0, 0, 0}), renderer_(nullptr), entity_(0) {
  collider_ = new Collider[MAX_ENTITIES];
  physics_ = new Physics[MAX_ENTITIES];
  sprite_ = new Sprite[MAX_ENTITIES];
  transform_ = new Transform[MAX_ENTITIES];
}

void ECS::initialize(SDL_Rect viewport, SDL_Renderer* renderer) {
  viewport_ = viewport;
  renderer_ = renderer;

  // Initialize game objects
}

void ECS::terminate() {
  // Do stuff
}

const SDL_Rect ECS::viewport() { return viewport_; }
const SDL_Renderer* ECS::renderer() { return renderer_; }

const Collider* ECS::collider() { return collider_; }
const Physics* ECS::physics() { return physics_; }
const Sprite* ECS::sprite() { return sprite_; }
const Transform* ECS::transform() { return transform_; }

int ECS::createEntity() {
  assert(entity_ < MAX_ENTITIES);
  entity_++;
  return entity_ - 1;  // Array index starts at 0
}

void ECS::input() { ProcessInput::input(); }

void ECS::update() {
  // Do nothing
}

void ECS::render(float delay) {
  // Do nothing
  (void)delay;
}
