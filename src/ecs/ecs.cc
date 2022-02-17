#include "ecs.h"

#include <SDL_image.h>
#include <assert.h>

#include "systems/choose_alien_direction.h"
#include "systems/render_collider.h"
#include "systems/render_sprite.h"
#include "systems/update_position.h"

ECS::ECS() : size_(0), screenWidth_(0), screenHeight_(0), renderer_(nullptr) {
  ai_ = new AI[kMaxSize_];
  collider_ = new Collider[kMaxSize_];
  physics_ = new Physics[kMaxSize_];
  sprite_ = new Sprite[kMaxSize_];
  transform_ = new Transform[kMaxSize_];
}

void ECS::initialize(int screenWidth, int screenHeight,
                     SDL_Renderer* renderer) {
  screenWidth_ = screenWidth;
  screenHeight_ = screenHeight;
  renderer_ = renderer;

  createAliens();
}

void ECS::terminate() {
  for (int i = 0; i < size_; i++) {
    SDL_DestroyTexture(sprite_[i].texture);
    sprite_[i].texture = nullptr;
  }
}

int ECS::size() { return size_; }

AI* ECS::ai() { return ai_; }

Collider* ECS::collider() { return collider_; }

Physics* ECS::physics() { return physics_; }

Sprite* ECS::sprite() { return sprite_; }

Transform* ECS::transform() { return transform_; }

void ECS::input(SDL_Event event) {
  //
  (void)event;
}

void ECS::update() {
  ChooseAlienDirection::update(*this);
  UpdatePosition::update(*this);
}

void ECS::render(SDL_Renderer* renderer, float delay) {
  RenderSprite::render(*this, renderer, delay);

#ifdef DEBUG
  RenderCollider::render(*this, renderer);
#endif
}

bool ECS::isOutOfBounds() {
  for (int i = 0; i < size_; i++) {
    int x = static_cast<int>(roundf(transform_[i].position.x));
    int y = static_cast<int>(roundf(transform_[i].position.y));
    if (x < 0 || x > screenWidth_) {
      return true;
    }
    if (y < 0 || y > screenHeight_) {
      return true;
    }
  }
  return false;
}

int ECS::createEntity() {
  assert(size_ < kMaxSize_);
  size_++;
  return size_ - 1;  // Array index starts at 0
}

void ECS::createAliens() {
  int alienWidth = 50;
  int alienHeight = 50;

  int rows = 5;
  int columns = 11;

  int spawnWidth = columns * alienWidth;
  int spawnHeight = rows * alienHeight;

  int startX = screenWidth_ / 2 - spawnWidth / 2 + alienWidth / 2;
  int startY = screenHeight_ / 4 - spawnHeight / 2 + alienHeight / 2;

  SDL_Texture* texture = nullptr;
  SDL_Surface* surface = IMG_Load("../../data/images/alien.png");
  texture = SDL_CreateTextureFromSurface(renderer_, surface);
  SDL_FreeSurface(surface);

  int spawnX = startX;
  int spawnY = startY;
  for (int i = 0; i < rows * columns; i++) {
    int entity = createEntity();

    transform_[entity].position.x = static_cast<float>(spawnX);
    transform_[entity].position.y = static_cast<float>(spawnY);

    collider_[entity].rect.w = alienWidth;
    collider_[entity].rect.h = alienHeight;

    physics_[entity].speed = 1.0f;

    ai_[entity].nextDirection = Direction::kLeft;
    ai_[entity].goalHeight = transform_[entity].position.y;

    sprite_[entity].texture = texture;

    spawnX += alienWidth;
    if ((i + 1) % columns == 0) {
      spawnX = startX;
      spawnY += alienHeight;
    }
  }
}
