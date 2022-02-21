#pragma once

#include <string>

#include "ecs/pools/pool.h"

class Engine;

class Bullets : public Pool {
 public:
  const int TOTAL = 300;
  const int WIDTH = 18;
  const float DELTA_VELOCITY = 5.0f;
  const char* TEXTURE_FILE = "circle.png";

  virtual void initialize() override;
};
