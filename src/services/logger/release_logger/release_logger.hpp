#pragma once

#include "../logger.hpp"

class ReleaseLogger : public Logger {
 public:
  void print(const std::string& text) override;
};
