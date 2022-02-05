#pragma once

#include "logging/logging.hpp"
#include "logging/debug_logging/debug_logging.hpp"
#include "logging/release_logging/release_logging.hpp"

class Locator {
 public:
  static Logging& logging();

 private:
#if DEBUG
  static DebugLogging logging_;
#else
  static ReleaseLogging logging_;
#endif
};
