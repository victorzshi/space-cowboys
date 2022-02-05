#pragma once

#include "logger/logger.hpp"

class Locator {
 public:
  static void initialize();
  static Logger& logger();

 private:
  static Logger* logger_;
};
