#pragma once

#include <string>

#include "ecs/pools/pool.h"

class Engine;

class Zappers : public Pool {
 public:
  const int TOTAL = 1000;
  const int WIDTH = 36;
  const float DELTA_VELOCITY = 2.5f;
  const char* TEXTURE_FILE = "poop.png";

  virtual void initialize() override;
};
