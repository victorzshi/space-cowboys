#pragma once

#include "types/types.h"

struct Timer {
  Uint64 previous;

  Uint64 elapsed(Uint64 current) { return current - previous; }
};
