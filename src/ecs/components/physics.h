#pragma once

#include "vector2/vector2.h"

struct Physics {
  float deltaVelocity;
  float deltaAcceleration;
  Vector2 velocity;
  Vector2 acceleration;
};
