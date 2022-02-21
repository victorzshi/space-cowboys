#pragma once

#include <string>

#include "ecs/pools/pool.h"
#include "types/types.h"

class Engine;

class Explosions : public Pool {
 public:
  const int TOTAL = 100;
  const Uint64 DURATION = 300;
  const char* TEXTURE_FILE = "explosion.png";

  virtual void initialize() override;
};
