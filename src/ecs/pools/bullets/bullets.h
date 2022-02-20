#pragma once

#include "ecs/pools/pool.h"

class Engine;

class Bullets : public Pool {
 public:
  Bullets();

  virtual void initialize(Engine& e) override;
};
