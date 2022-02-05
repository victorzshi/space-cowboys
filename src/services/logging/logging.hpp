#pragma once

#include <string>

class Logging {
 public:
  virtual ~Logging() = default;
  virtual void print(const std::string& text) = 0;
};
