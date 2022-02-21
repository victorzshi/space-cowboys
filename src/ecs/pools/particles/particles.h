#pragma once

#include <string>

#include "ecs/pools/pool.h"
#include "types/types.h"

class Engine;

class Particles : public Pool {
 public:
  const int TOTAL = 100;
  const int WIDTH = 72;
  const Uint64 DURATION = 150;
  const char* TEXTURE_FILE = "explosion.png";

  virtual void initialize() override;
};
