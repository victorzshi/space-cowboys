#include "ecs.h"

#include <SDL_image.h>
#include <assert.h>

#include "systems/choose_alien_direction.h"
#include "systems/process_tank_input.h"
#include "systems/render_collider.h"
#include "systems/render_sprite.h"
#include "systems/resolve_bullet_hit.h"
#include "systems/update_alien_position.h"
#include "systems/update_bullet_position.h"
#include "systems/update_tank_position.h"

ECS::ECS() : size_(0), screenWidth_(0), screenHeight_(0), renderer_(nullptr) {
  active = new Active[kMaxSize_];
  ai = new AI[kMaxSize_];
  physics = new Physics[kMaxSize_];
  sprite = new Sprite[kMaxSize_];
  transform = new Transform[kMaxSize_];
}

void ECS::initialize(int screenWidth, int screenHeight,
                     SDL_Renderer* renderer) {
  screenWidth_ = screenWidth;
  screenHeight_ = screenHeight;
  renderer_ = renderer;

  initializeTank();
  initializeAliens();
  initializeBullets();
}

void ECS::terminate() {
  for (int i = 0; i < size_; i++) {
    SDL_DestroyTexture(sprite[i].texture);
    sprite[i].texture = nullptr;
  }
}

void ECS::input(SDL_Event event) { ProcessTankInput::input(*this, event); }

void ECS::update() {
  UpdateTankPosition::update(*this);
  ChooseAlienDirection::update(*this);
  UpdateAlienPosition::update(*this);
  UpdateBulletPosition::update(*this);
  ResolveBulletHit::update(*this);
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

void ECS::initializeAliens() {
  int alienWidth = 72;
  int alienHeight = 72;

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

    active[id].state = true;

    transform[id].position.x = static_cast<float>(spawnX);
    transform[id].position.y = static_cast<float>(spawnY);

    physics[id].deltaVelocity = 1.0f;
    physics[id].collider.w = alienWidth;
    physics[id].collider.h = alienHeight;

    ai[id].nextDirection = Direction::kLeft;
    ai[id].goalHeight = transform[id].position.y;
    ai[id].isPathEnd = false;

    sprite[id].texture = texture;

    spawnX += alienWidth;
    if ((i + 1) % columns == 0) {
      spawnX = startX;
      spawnY += alienHeight;
    }
  }
}

void ECS::initializeTank() {
  SDL_Texture* texture =
      Utils::createTexture(renderer_, "../../data/images/tank.png");

  int id = createEntity();

  allIds.push_back(id);
  tankIds.push_back(id);

  active[id].state = true;

  transform[id].position.x = static_cast<float>(screenWidth_ / 2);
  transform[id].position.y = static_cast<float>(screenHeight_ - 100);

  physics[id].deltaAcceleration = 0.1f;
  physics[id].collider.w = 72;
  physics[id].collider.h = 72;

  sprite[id].texture = texture;
}

void ECS::initializeBullets() {
  SDL_Texture* texture =
      Utils::createTexture(renderer_, "../../data/images/bullet.png");

  int totalBullets = 10;

  for (int i = 0; i < totalBullets; i++) {
    int id = createEntity();

    allIds.push_back(id);
    bulletIds.push_back(id);

    active[id].state = false;

    physics[id].deltaVelocity = 5.0f;
    physics[id].collider.w = 36;
    physics[id].collider.h = 36;

    sprite[id].texture = texture;
  }
}
