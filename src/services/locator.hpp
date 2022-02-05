#pragma once

#include "logging/logging.hpp"
#include "logging/null_logging/null_logging.hpp"

class Locator {
 public:
  static void initialize();
  static Logging& getLogging();
  static void provide(Logging* service);

 private:
#if DEBUG
  static Logging* service_;
  static NullLogging* nullService_;
#else
  // TODO: Set release mode logging.
#endif
};
