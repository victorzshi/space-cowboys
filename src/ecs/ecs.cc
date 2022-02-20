#include "ecs.h"

#include <SDL_image.h>
#include <assert.h>

#include "ecs/components/ai.h"
#include "ecs/components/collider.h"
#include "ecs/components/physics.h"
#include "ecs/components/sprite.h"
#include "ecs/components/transform.h"
#include "ecs/systems/input_ai/input_ai.h"
#include "ecs/systems/process_input/process_input.h"
#include "ecs/systems/render_collider/render_collider.h"
#include "ecs/systems/render_sprite/render_sprite.h"
#include "ecs/systems/update_position/update_position.h"

ECS::ECS() : id_(0), viewport_({0, 0, 0, 0}), renderer_(nullptr) {
  ai_ = new AI[MAX_ENTITIES];
  collider_ = new Collider[MAX_ENTITIES];
  physics_ = new Physics[MAX_ENTITIES];
  sprite_ = new Sprite[MAX_ENTITIES];
  transform_ = new Transform[MAX_ENTITIES];
}

void ECS::initialize(SDL_Rect viewport, SDL_Renderer* renderer) {
  viewport_ = viewport;
  renderer_ = renderer;

  aliens_.initialize(*this, 200);
  bullets_.initialize(*this, 1000);
}

void ECS::terminate() {
  // Do stuff
}

SDL_Rect& ECS::viewport() { return viewport_; }
SDL_Renderer* ECS::renderer() { return renderer_; }

AI* ECS::ai() { return ai_; }
Collider* ECS::collider() { return collider_; }
Physics* ECS::physics() { return physics_; }
Sprite* ECS::sprite() { return sprite_; }
Transform* ECS::transform() { return transform_; }

Aliens& ECS::aliens() { return aliens_; }
Bullets& ECS::bullets() { return bullets_; }

int ECS::createEntity() {
  assert(id_ < MAX_ENTITIES);
  id_++;
  return id_ - 1;  // Array index starts at 0
}

SDL_Texture* ECS::createTexture(std::string file) {
  std::string relativePath = "../../data/images/" + file;

  SDL_Texture* texture = nullptr;
  SDL_Surface* surface = IMG_Load(relativePath.c_str());
  texture = SDL_CreateTextureFromSurface(renderer_, surface);
  SDL_FreeSurface(surface);

  return texture;
}

bool ECS::isOutOfBounds(SDL_Rect rect) {
  int topLeftX = rect.x;
  int topLeftY = rect.y;
  int bottomRightX = rect.x + rect.w;
  int bottomRightY = rect.y + rect.h;

  return topLeftX < viewport_.x || topLeftY < viewport_.y ||
         bottomRightX > viewport_.w || bottomRightY > viewport_.h;
}

void ECS::input() {
  ProcessInput::input(*this);
  InputAI::input(*this);
}

void ECS::update() {
  //
  UpdatePosition::update(*this);
}

void ECS::render(float delay) {
  RenderSprite::render(*this, delay);

#ifdef DEBUG
  RenderCollider::render(*this);
#endif
}
