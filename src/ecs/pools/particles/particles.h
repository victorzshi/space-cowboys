#pragma once

#include <string>

#include "ecs/pools/pool.h"

class Engine;

class Particles : public Pool {
 public:
  const int TOTAL = 100;
  const int WIDTH = 72;
  const float DELTA_VELOCITY = 5.0f;
  const char* TEXTURE_FILE = "explosion.png";

  virtual void initialize() override;
};
