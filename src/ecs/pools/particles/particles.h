#pragma once

#include <string>

#include "ecs/pools/pool.h"
#include "types/types.h"

class Engine;

class Particles : public Pool {
 public:
  const int TOTAL = 500;
  const int WIDTH = 5;
  const Uint64 DURATION = 1000;
  const char* TEXTURE_FILE = "purple-square.png";

  virtual void initialize() override;
};
