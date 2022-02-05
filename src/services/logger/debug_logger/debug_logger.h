#pragma once

#include "../logger.h"

class DebugLogger : public Logger {
 public:
  DebugLogger();
  void print(const std::string& text) override;
};
