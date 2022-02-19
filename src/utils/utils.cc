#include "utils.h"

#include <cmath>

bool Utils::isEqual(float a, float b, float epsilon) {
  return abs(a - b) <= epsilon * (abs(a) + abs(b) + 1.0f);
}
