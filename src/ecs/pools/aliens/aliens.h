#pragma once

#include <vector>

#include "ecs/pools/pool.h"

class Engine;
struct Vector2;
struct Grid;

class Aliens : public Pool {
 public:
  const int ROWS = 40;
  const int COLUMNS = 20;
  const int WIDTH = 72;
  const float DELTA_VELOCITY = 5.0f;
  const char* TEXTURE_FILE = "space-invader.png";

  virtual void initialize() override;

 private:
  std::vector<Vector2> createPositions(Grid grid);
};
