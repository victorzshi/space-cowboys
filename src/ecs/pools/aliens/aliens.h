#pragma once

#include <vector>

#include "ecs/pools/pool.h"
#include "types/types.h"

class Engine;
struct Vector2;
struct Grid;

class Aliens : public Pool {
 public:
  const int ROWS = 100;
  const int COLUMNS = 20;
  const int WIDTH = 36;
  const int GUTTER = 18;
  const Uint64 ZAPPER_COOLDOWN = 3000;
  const float DELTA_VELOCITY = 5.0f;
  const char* TEXTURE_FILE = "space-invader.png";

  virtual void initialize() override;

 private:
  std::vector<Vector2> createPositions(Grid grid);
};
