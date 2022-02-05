#pragma once

#include "logger/debug_logger/debug_logger.hpp"
#include "logger/logger.hpp"
#include "logger/release_logger/release_logger.hpp"

class Locator {
 public:
  static Logger& logger();

 private:
#if DEBUG
  static DebugLogger logger_;
#else
  static ReleaseLogger logger_;
#endif
};
