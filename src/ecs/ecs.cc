#include "ecs.h"

#include <SDL_image.h>
#include <assert.h>
#include <time.h>

#include "systems/movement.h"
#include "systems/render_sprite.h"
#include "systems/update_position.h"

ECS::ECS() : size_(0) {}

void ECS::initialize(int screenWidth, int screenHeight,
                     SDL_Renderer* renderer) {
  physics_ = new Physics[kMaxSize];
  sprites_ = new Sprite[kMaxSize];
  transforms_ = new Transform[kMaxSize];

  // Load space invader image
  SDL_Texture* spaceInvader = nullptr;
  SDL_Surface* loadedSurface = IMG_Load("../../data/space-invader.png");
  spaceInvader = SDL_CreateTextureFromSurface(renderer, loadedSurface);
  SDL_FreeSurface(loadedSurface);
  Sprite sprite;
  sprite.texture = spaceInvader;

  // Initialize random number
  unsigned int seed = static_cast<unsigned int>(time(nullptr));
  srand(seed);

  for (int i = 0; i < kMaxSize; i++) {
    int entity = createEntity();
    Transform transform;
    transform.position.x = static_cast<float>(rand() % screenWidth);
    transform.position.y = static_cast<float>(rand() % screenHeight);
    transform.width = 50;
    transform.height = 50;
    addTransform(entity, transform);
    Physics physics;
    physics.speed = 0.1f;
    physics.velocity.y = static_cast<float>(rand() % 5 + 1);
    addPhysics(entity, physics);
    addSprite(entity, sprite);
  }
}

int ECS::size() { return size_; }

Physics* ECS::physics() { return physics_; }

Sprite* ECS::sprites() { return sprites_; }

Transform* ECS::transforms() { return transforms_; }

void ECS::input(SDL_Event event) {
  //
  Movement::input(*this, event);
}

void ECS::update() {
  //
  UpdatePosition::update(*this);
}

void ECS::render(SDL_Renderer* renderer, float delay) {
  RenderSprite::render(*this, renderer, delay);
}

int ECS::createEntity() {
  assert(size_ < kMaxSize);

  ++size_;
  return size_ - 1;
}

void ECS::addPhysics(int entity, Physics physics) {
  physics_[entity] = physics;
}

void ECS::addSprite(int entity, Sprite sprite) { sprites_[entity] = sprite; }

void ECS::addTransform(int entity, Transform transform) {
  transforms_[entity] = transform;
}
