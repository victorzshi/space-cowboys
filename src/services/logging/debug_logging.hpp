#include <iostream>

#include "logging.hpp"

class DebugLogging : public Logging {
 public:
  void print() override;
};
