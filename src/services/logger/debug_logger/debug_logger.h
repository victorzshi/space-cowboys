#pragma once

#include "services/logger/logger.h"

class DebugLogger : public Logger {
 public:
  DebugLogger();
  virtual void print(const std::string& text) override;
};
