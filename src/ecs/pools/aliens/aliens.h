#pragma once

#include <vector>

#include "ecs/pools/pool.h"

class Engine;
struct Vector2;
struct Grid;

class Aliens : public Pool {
 public:
  const int ROWS = 4;
  const int COLUMNS = 11;
  const int WIDTH = 72;
  const float DELTA_VELOCITY = 5.0f;
  const char* TEXTURE_FILE = "alien.png";

  Aliens();

  virtual void initialize() override;

 private:
  std::vector<Vector2> createPositions(Grid grid);
};
