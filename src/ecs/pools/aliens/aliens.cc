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

void Aliens::initialize() {
  Locator::logger().print("Initializing aliens...");

  Grid grid;
  grid.cell.width = WIDTH;
  grid.cell.height = WIDTH;
  grid.gutter.width = WIDTH / 4;
  grid.gutter.height = WIDTH / 4;
  grid.rows = ROWS;
  grid.columns = COLUMNS;
  grid.center = {e_->viewport().w / 2, ROWS * WIDTH};

  SDL_Texture* texture = e_->createTexture(TEXTURE_FILE);

  int index = 0;
  std::vector<Vector2> positions = createPositions(grid);
  for (size_t i = 0; i < positions.size(); i++) {
    int id = e_->createEntity();

    transform_[id].position = positions[i];

    physics_[id].velocity.x = -DELTA_VELOCITY;

    collider_[id].box.w = WIDTH;
    collider_[id].box.h = WIDTH;

    ai_[id].nextDirection = Direction::LEFT;
    ai_[id].goalHeight = transform_[id].position.y;
    ai_[id].isPathEnd = false;

    sprite_[id].texture = texture;

    index = id;
  }

  begin_ = index - (ROWS * COLUMNS - 1);
  size_ = index + 1;
  end_ = index;
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
