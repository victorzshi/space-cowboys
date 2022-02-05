#pragma once

#include "../logging.hpp"

class DebugLogging : public Logging {
 public:
  DebugLogging();
  void print(const std::string& text) override;
};
