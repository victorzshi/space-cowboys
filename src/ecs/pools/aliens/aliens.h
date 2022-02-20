#pragma once

#include <vector>

#include "ecs/pools/pool.h"

class Engine;
struct Vector2;
struct Grid;

class Aliens : public Pool {
 public:
  Aliens();

  virtual void initialize() override;

 private:
  std::vector<Vector2> createPositions(Grid grid);
};
