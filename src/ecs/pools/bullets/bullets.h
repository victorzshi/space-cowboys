#pragma once

#include <string>

#include "ecs/pools/pool.h"

class Engine;

class Bullets : public Pool {
 public:
  const int TOTAL = 500;
  const int WIDTH = 9;
  const float DELTA_VELOCITY = 5.0f;
  const char* TEXTURE_FILE = "white-circle.png";

  virtual void initialize() override;
};
