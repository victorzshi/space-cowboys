#pragma once

#include <string>

#include "ecs/pools/pool.h"
#include "types/types.h"

class Engine;

class Tanks : public Pool {
 public:
  const int TOTAL = 1;
  const int WIDTH = 72;
  const Uint64 BULLET_COOLDOWN = 500;
  const float DELTA_VELOCITY = 10.0f;
  const char* TEXTURE_FILE = "tank.png";

  virtual void initialize() override;
};
