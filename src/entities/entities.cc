#include "entities.h"

#include <SDL_image.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

#include "systems/movement.h"
#include "systems/render_sprite.h"
#include "systems/update_position.h"

Entities::Entities() : size_(0) {}

void Entities::initialize(int screenWidth, int screenHeight,
                          SDL_Renderer* renderer) {
  physics_ = new Physics[kMaxSize];
  sprites_ = new Sprite[kMaxSize];
  transforms_ = new Transform[kMaxSize];

  // Load space invader image
  SDL_Texture* spaceInvader = nullptr;
  SDL_Surface* loadedSurface = IMG_Load("../../data/space-invader.png");
  spaceInvader = SDL_CreateTextureFromSurface(renderer, loadedSurface);
  SDL_FreeSurface(loadedSurface);
  Sprite sprite = {spaceInvader};

  // Initialize random number
  unsigned int seed = static_cast<unsigned int>(time(nullptr));
  srand(seed);

  for (int i = 0; i < kMaxSize; i++) {
    int entity = createEntity();
    int width = rand() % screenWidth;
    int height = rand() % screenHeight;
    addTransform(entity, {Vec2(width, height), 50, 50});
    addPhysics(entity, {0.1, Vec2(0.0, rand() % 5 + 1)});
    addSprite(entity, sprite);
  }
}

int Entities::size() { return size_; }

Physics* Entities::physics() { return physics_; }

Sprite* Entities::sprites() { return sprites_; }

Transform* Entities::transforms() { return transforms_; }

void Entities::input(SDL_Event event) {
  //
  Movement::input(*this, event);
}

void Entities::update() {
  //
  UpdatePosition::update(*this);
}

void Entities::render(SDL_Renderer* renderer, double delay) {
  RenderSprite::render(*this, renderer, delay);
}

int Entities::createEntity() {
  assert(size_ < kMaxSize);

  ++size_;
  return size_ - 1;
}

void Entities::addPhysics(int entity, Physics physics) {
  physics_[entity] = physics;
}

void Entities::addSprite(int entity, Sprite sprite) {
  sprites_[entity] = sprite;
}

void Entities::addTransform(int entity, Transform transform) {
  transforms_[entity] = transform;
}
