#pragma once

#include <vector>

#include "ecs/pools/pool.h"

class Engine;
struct Vector2;
struct Grid;

class Aliens : public Pool {
 public:
  Aliens();

  virtual void initialize(Engine& e, int total) override;

  virtual int begin() override;
  virtual int active() override;
  virtual int end() override;

  virtual void activate(Engine& e, int id) override;

  virtual void deactivate(Engine& e, int id) override;

 private:
  int begin_;
  int active_;
  int end_;

  std::vector<Vector2> createPositions(Grid grid);
};
