#pragma once

#include <string>

#include "ecs/pools/pool.h"
#include "types/types.h"

class Engine;

class Tanks : public Pool {
 public:
  const int TOTAL = 5;
  const int WIDTH = 72;
  const Uint64 BULLET_COOLDOWN = 100;
  const float DELTA_VELOCITY = 20.0f;
  const char* TEXTURE_FILE = "cowboy.png";

  virtual void initialize() override;
};
