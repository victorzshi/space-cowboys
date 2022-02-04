#pragma once

#include "logging/logging.hpp"

class Locator {
 public:
  static Logging* getLogging();
  static void provide(Logging* service);

 private:
  static Logging* service_;
};
