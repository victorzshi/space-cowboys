#pragma once

#include <string>

#include "ecs/pools/pool.h"

class Engine;

class Tanks : public Pool {
 public:
  const int TOTAL = 3;
  const int WIDTH = 72;
  const float DELTA_VELOCITY = 5.0f;
  const char* TEXTURE_FILE = "tank.png";

  virtual void initialize() override;
};
