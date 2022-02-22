#pragma once

#include <string>

#include "ecs/pools/pool.h"
#include "types/types.h"

class Engine;

class Explosions : public Pool {
 public:
  const int TOTAL = 100;
  const Uint64 DURATION = 500;
  const char* TEXTURE_FILE = "boom.png";

  virtual void initialize() override;
};
