#pragma once

class Logging {
 public:
  virtual ~Logging() {}
  virtual void print() = 0;
};
