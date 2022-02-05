#pragma once

#include "../logger.h"

class ReleaseLogger : public Logger {
 public:
  void print(const std::string& text) override;
};
