#include "entities.h"

#include <SDL_image.h>
#include <assert.h>
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
  Sprite sprite;
  sprite.texture = spaceInvader;

  // Initialize random number
  unsigned int seed = static_cast<unsigned int>(time(nullptr));
  srand(seed);

  for (int i = 0; i < kMaxSize; i++) {
    int entity = createEntity();
    float width = static_cast<float>(rand() % screenWidth);
    float height = static_cast<float>(rand() % screenHeight);
    Transform transform;
    transform.position = Vector2{width, height};
    transform.width = 50;
    transform.height = 50;
    addTransform(entity, transform);
    Physics physics;
    physics.speed = 0.1f;
    float falling = static_cast<float>(rand() % 5 + 1);
    physics.velocity = Vector2{0.0, falling};
    addPhysics(entity, physics);
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

void Entities::render(SDL_Renderer* renderer, float delay) {
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
