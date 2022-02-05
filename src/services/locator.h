#pragma once

#include "logger/logger.h"

class Locator {
 public:
  static void initialize();
  static Logger& logger();

 private:
  static Logger* logger_;
};
