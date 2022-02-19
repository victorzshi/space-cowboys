#pragma once

#include <cmath>

class Utils {
 public:
  static inline bool isEqual(float a, float b, float epsilon = 1.0f / 1000) {
    return abs(a - b) <= epsilon * (abs(a) + abs(b) + 1.0f);
  }
};
