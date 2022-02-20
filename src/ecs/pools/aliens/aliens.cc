#include "aliens.h"

#include <SDL.h>
#include <assert.h>

#include "ecs/components/ai.h"
#include "ecs/components/collider.h"
#include "ecs/components/physics.h"
#include "ecs/components/sprite.h"
#include "ecs/components/transform.h"
#include "ecs/engine.h"
#include "services/locator.h"
#include "vector2/vector2.h"

struct Grid {
  struct Size {
    int width;
    int height;
  };
  Size cell;
  Size gutter;
  int rows;
  int columns;
  SDL_Point center;
};

Aliens::Aliens() : begin_(0), active_(0), end_(0) {}

void Aliens::initialize(Engine& e, int total) {
  (void)total;

  Locator::logger().print("Initializing aliens...");

  int rows = 4;
  int columns = 11;
  int width = 36;
  float deltaVelocity = 1.0f;

  Grid grid;
  grid.cell.width = width;
  grid.cell.height = width;
  grid.gutter.width = width / 4;
  grid.gutter.height = width / 4;
  grid.rows = rows;
  grid.columns = columns;
  grid.center = {e.viewport().w / 2, rows * width};

  SDL_Texture* texture = e.createTexture("alien.png");

  AI* ai = e.ai();
  Collider* collider = e.collider();
  Physics* physics = e.physics();
  Sprite* sprite = e.sprite();
  Transform* transform = e.transform();

  int index = 0;
  std::vector<Vector2> positions = createPositions(grid);
  for (size_t i = 0; i < positions.size(); i++) {
    int id = e.createEntity();

    transform[id].position = positions[i];

    physics[id].velocity.x = -deltaVelocity;

    collider[id].box.w = width;
    collider[id].box.h = width;

    ai[id].nextDirection = Direction::LEFT;
    ai[id].goalHeight = transform[id].position.y;
    ai[id].isPathEnd = false;

    sprite[id].texture = texture;

    index = id;
  }

  begin_ = index - (rows * columns - 1);
  active_ = index + 1;
  end_ = index;
}

int Aliens::begin() { return begin_; }
int Aliens::active() { return active_; }
int Aliens::end() { return end_; }

void Aliens::activate(Engine& e, int id) {
  Locator::logger().print("Activating alien...");
  Locator::logger().print(std::to_string(id));

  if (active_ > end_) return;

  Transform* transform = e.transform();

  // TODO(Victor): Activate alien

  Transform temp = transform[active_];
  transform[active_] = transform[id];
  transform[id] = temp;

  active_++;
}

void Aliens::deactivate(Engine& e, int id) {
  Locator::logger().print("Deactivating alien...");
  Locator::logger().print(std::to_string(id));

  assert(id < active_);

  Transform* transform = e.transform();

  active_--;

  // TODO(Victor): Could probably make this a generic function in ECS.
  Transform temp = transform[active_];
  transform[active_] = transform[id];
  transform[id] = temp;
}

std::vector<Vector2> Aliens::createPositions(Grid grid) {
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
