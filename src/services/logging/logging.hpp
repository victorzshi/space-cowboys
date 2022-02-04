#pragma once

#include <string>

class Logging {
 public:
  virtual ~Logging() {}
  virtual void print(const std::string& text) = 0;
};
