#pragma once

#include "logging/logging.hpp"
#include "logging/null_logging/null_logging.hpp"

class Locator {
 public:
  static void initialize();
  static Logging& getLogging();
  static void provide(Logging* service);

 private:
  static Logging* service_;
  static NullLogging* nullService_;
};
