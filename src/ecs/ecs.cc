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
  int rows = 4;
  int columns = 11;
  int alienWidth = 36;
  float alienDeltaVelocity = 1.0f;
  SDL_Point center = {screenWidth_ / 2, rows * alienWidth};

  Grid grid;
  grid.cell.width = alienWidth;
  grid.cell.height = alienWidth;
  grid.gutter.width = alienWidth / 4;
  grid.gutter.height = alienWidth / 4;
  grid.rows = rows;
  grid.columns = columns;
  grid.center = center;

  SDL_Texture* texture =
      Utils::createTexture(renderer_, "../../data/images/alien.png");

  std::vector<Vector2> positions = generateGridPositions(grid);
  for (size_t i = 0; i < positions.size(); i++) {
    int id = createEntity();

    allIds.push_back(id);
    alienIds.push_back(id);

    active[id].state = true;

    transform[id].position = positions[i];

    physics[id].deltaVelocity = alienDeltaVelocity;
    physics[id].collider.w = alienWidth;
    physics[id].collider.h = alienWidth;

    ai[id].nextDirection = Direction::kLeft;
    ai[id].goalHeight = transform[id].position.y;
    ai[id].isPathEnd = false;

    sprite[id].texture = texture;
  }
}

void ECS::initializeTank() {
  SDL_Point center = {screenWidth_ / 2, screenHeight_ - 50};
  int tankWidth = 72;
  float tankDeltaAcceleration = 0.1f;

  SDL_Texture* texture =
      Utils::createTexture(renderer_, "../../data/images/tank.png");

  int id = createEntity();

  allIds.push_back(id);
  tankIds.push_back(id);

  active[id].state = true;

  transform[id].position.x = static_cast<float>(center.x);
  transform[id].position.y = static_cast<float>(center.y);

  physics[id].deltaAcceleration = tankDeltaAcceleration;
  physics[id].collider.w = tankWidth;
  physics[id].collider.h = tankWidth;

  sprite[id].texture = texture;
}

void ECS::initializeBullets() {
  int totalBullets = 10;
  int bulletWidth = 18;
  float bulletDeltaVelocity = 5.0f;

  SDL_Texture* texture =
      Utils::createTexture(renderer_, "../../data/images/tank-bullet.png");

  for (int i = 0; i < totalBullets; i++) {
    int id = createEntity();

    allIds.push_back(id);
    bulletIds.push_back(id);

    active[id].state = false;

    physics[id].deltaVelocity = bulletDeltaVelocity;
    physics[id].collider.w = bulletWidth;
    physics[id].collider.h = bulletWidth;

    sprite[id].texture = texture;
  }
}

void ECS::initializeWalls() {
  SDL_Point center = {screenWidth_ / 2, screenHeight_ - 200};
  int totalWalls = 4;
  int rows = 3;
  int columns = 5;
  int wallWidth = 36;

  std::vector<Grid> grids;
  int spawnX = screenWidth_ / totalWalls / 2;
  int spawnY = center.y;
  for (int i = 0; i < totalWalls; i++) {
    Grid grid;
    grid.cell.width = wallWidth;
    grid.cell.height = wallWidth;
    grid.gutter.width = 0;
    grid.gutter.height = 0;
    grid.rows = rows;
    grid.columns = columns;
    grid.center.x = spawnX;
    grid.center.y = spawnY;

    grids.push_back(grid);

    spawnX += screenWidth_ / totalWalls;
  }

  std::vector<Vector2> positions;
  for (size_t i = 0; i < grids.size(); i++) {
    std::vector<Vector2> currentPositions = generateGridPositions(grids[i]);

    for (size_t j = 0; j < currentPositions.size(); j++) {
      positions.push_back(currentPositions[j]);
    }
  }

  SDL_Texture* texture =
      Utils::createTexture(renderer_, "../../data/images/wall.png");

  for (size_t i = 0; i < positions.size(); i++) {
    int id = createEntity();

    allIds.push_back(id);
    wallIds.push_back(id);

    active[id].state = true;

    transform[id].position = positions[i];

    int x = static_cast<int>(roundf(positions[i].x));
    int y = static_cast<int>(roundf(positions[i].y));

    physics[id].collider.x = x - (wallWidth / 2);
    physics[id].collider.y = y - (wallWidth / 2);
    physics[id].collider.w = wallWidth;
    physics[id].collider.h = wallWidth;

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
