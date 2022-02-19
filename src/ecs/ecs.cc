#include "ecs.h"

#include <assert.h>

#include "systems/process_input.h"
#include "systems/render_collider.h"
#include "systems/update_position.h"

ECS::ECS() : id_(0), viewport_({0, 0, 0, 0}), renderer_(nullptr) {
  collider_ = new Collider[MAX_ENTITIES];
  physics_ = new Physics[MAX_ENTITIES];
  sprite_ = new Sprite[MAX_ENTITIES];
  transform_ = new Transform[MAX_ENTITIES];
}

void ECS::initialize(SDL_Rect viewport, SDL_Renderer* renderer) {
  viewport_ = viewport;
  renderer_ = renderer;

  bullets_.initialize(*this, 10);
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

Bullets& ECS::bullets() { return bullets_; }

int ECS::createEntity() {
  assert(id_ < MAX_ENTITIES);
  id_++;
  return id_ - 1;  // Array index starts at 0
}

void ECS::input() {
  //
  ProcessInput::input(*this);
}

void ECS::update() {
  //
  UpdatePosition::update(*this);
}

void ECS::render(float delay) {
  (void)delay;

#ifdef DEBUG
  RenderCollider::render(*this);
#endif
}
