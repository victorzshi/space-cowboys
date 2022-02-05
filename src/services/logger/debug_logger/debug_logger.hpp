#pragma once

#include "../logger.hpp"

class DebugLogger : public Logger {
 public:
  DebugLogger();
  void print(const std::string& text) override;
};
