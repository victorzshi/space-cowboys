#include "ecs.h"

#include <SDL_image.h>
#include <assert.h>

#include "systems/choose_alien_direction.h"
#include "systems/process_tank_input.h"
#include "systems/render_collider.h"
#include "systems/render_sprite.h"
#include "systems/update_alien_position.h"
#include "systems/update_tank_position.h"

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
  createTank();
}

void ECS::terminate() {
  for (int i = 0; i < size_; i++) {
    SDL_DestroyTexture(sprite_[i].texture);
    sprite_[i].texture = nullptr;
  }
}

AI* ECS::ai() { return ai_; }

Collider* ECS::collider() { return collider_; }

Physics* ECS::physics() { return physics_; }

Sprite* ECS::sprite() { return sprite_; }

Transform* ECS::transform() { return transform_; }

void ECS::input(SDL_Event event) { ProcessTankInput::input(*this, event); }

void ECS::update() {
  UpdateTankPosition::update(*this);
  ChooseAlienDirection::update(*this);
  UpdateAlienPosition::update(*this);
}

void ECS::render(SDL_Renderer* renderer, float delay) {
  RenderSprite::render(*this, renderer, delay);

#ifdef DEBUG
  RenderCollider::render(*this, renderer);
#endif
}

bool ECS::isOutOfBounds(SDL_Rect rect) {
  int topLeftX = rect.x;
  int topLeftY = rect.y;
  int bottomRightX = rect.x + rect.w;
  int bottomRightY = rect.y + rect.h;

  return topLeftX < 0 || topLeftY < 0 || bottomRightX > screenWidth_ ||
         bottomRightY > screenHeight_;
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

  SDL_Texture* texture =
      Utils::createTexture(renderer_, "../../data/images/alien.png");

  int spawnX = startX;
  int spawnY = startY;
  for (int i = 0; i < rows * columns; i++) {
    int id = createEntity();

    allIds.push_back(id);
    alienIds.push_back(id);

    transform_[id].position.x = static_cast<float>(spawnX);
    transform_[id].position.y = static_cast<float>(spawnY);

    collider_[id].rect.w = alienWidth;
    collider_[id].rect.h = alienHeight;

    physics_[id].deltaVelocity = 1.0f;

    ai_[id].nextDirection = Direction::kLeft;
    ai_[id].goalHeight = transform_[id].position.y;
    ai_[id].isPathEnd = false;

    sprite_[id].texture = texture;

    spawnX += alienWidth;
    if ((i + 1) % columns == 0) {
      spawnX = startX;
      spawnY += alienHeight;
    }
  }
}

void ECS::createTank() {
  SDL_Texture* texture =
      Utils::createTexture(renderer_, "../../data/images/tank.png");

  int id = createEntity();

  allIds.push_back(id);
  tankIds.push_back(id);

  transform_[id].position.x = static_cast<float>(screenWidth_ / 2);
  transform_[id].position.y = static_cast<float>(screenHeight_ - 100);

  physics_[id].deltaAcceleration = 0.1f;

  collider_[id].rect.w = 50;
  collider_[id].rect.h = 50;

  sprite_[id].texture = texture;
}
