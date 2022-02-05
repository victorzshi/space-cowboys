#pragma once

#include <string>

class Logger {
 public:
  virtual ~Logger() {}
  virtual void print(const std::string& text) = 0;
};
