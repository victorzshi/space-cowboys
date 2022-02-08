#pragma once

#include "../logger.h"

class ReleaseLogger : public Logger {
 public:
  virtual void print(const std::string& text) override;
};
