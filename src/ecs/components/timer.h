#pragma once

#include "types/types.h"

class Timer {
 public:
  Uint64 previous;

  Uint64 elapsed(Uint64 current) { return current - previous; }
};
