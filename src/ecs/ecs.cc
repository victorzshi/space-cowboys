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
  initializeWalls();
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
  int alienSize = 72;

  Grid grid;
  grid.cell.width = alienSize;
  grid.cell.height = alienSize;
  grid.gutter.width = alienSize / 4;
  grid.gutter.height = alienSize / 4;
  grid.rows = 5;
  grid.columns = 11;
  grid.center.x = screenWidth_ / 2;
  grid.center.y = screenHeight_ / 4;

  SDL_Texture* texture =
      Utils::createTexture(renderer_, "../../data/images/alien.png");

  std::vector<Vector2> positions = generateGridPositions(grid);
  for (size_t i = 0; i < positions.size(); i++) {
    int id = createEntity();

    allIds.push_back(id);
    alienIds.push_back(id);

    active[id].state = true;

    transform[id].position = positions[i];

    physics[id].deltaVelocity = 1.0f;
    physics[id].collider.w = alienSize;
    physics[id].collider.h = alienSize;

    ai[id].nextDirection = Direction::kLeft;
    ai[id].goalHeight = transform[id].position.y;
    ai[id].isPathEnd = false;

    sprite[id].texture = texture;
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

void ECS::initializeWalls() {
  int wallSize = 48;

  Grid grid;
  grid.cell.width = wallSize;
  grid.cell.height = wallSize;
  grid.gutter.width = 0;
  grid.gutter.height = 0;
  grid.rows = 4;
  grid.columns = 4;
  grid.center.x = screenWidth_ / 2;
  grid.center.y = screenHeight_ - 300;

  SDL_Texture* texture =
      Utils::createTexture(renderer_, "../../data/images/wall.png");

  std::vector<Vector2> positions = generateGridPositions(grid);
  // TODO(Victor): Create 4 grids and join them.

  for (size_t i = 0; i < positions.size(); i++) {
    int id = createEntity();

    allIds.push_back(id);
    wallIds.push_back(id);

    active[id].state = true;

    transform[id].position = positions[i];

    int x = static_cast<int>(roundf(positions[i].x));
    int y = static_cast<int>(roundf(positions[i].y));

    physics[id].collider.x = x - (wallSize / 2);
    physics[id].collider.y = y - (wallSize / 2);
    physics[id].collider.w = wallSize;
    physics[id].collider.h = wallSize;

    sprite[id].texture = texture;
  }
}

std::vector<Vector2> ECS::generateGridPositions(Grid grid) {
  int gridWidth = grid.cell.width * grid.columns;
  gridWidth += grid.gutter.width * (grid.columns - 1);
  int gridHeight = grid.cell.height * grid.rows;
  gridHeight += grid.gutter.height * (grid.rows - 1);

  int startX = grid.center.x - gridWidth / 2 + grid.cell.width / 2;
  int startY = grid.center.y - gridHeight / 2 + grid.cell.height / 2;

  int spawnX = startX;
  int spawnY = startY;

  std::vector<Vector2> positions;
  for (int i = 0; i < grid.rows * grid.columns; i++) {
    Vector2 position;

    position.x = static_cast<float>(spawnX);
    position.y = static_cast<float>(spawnY);

    positions.push_back(position);

    spawnX += grid.cell.width + grid.gutter.width;
    if ((i + 1) % grid.columns == 0) {
      spawnX = startX;
      spawnY += grid.cell.height + grid.gutter.height;
    }
  }

  return positions;
}
