#include "logging.hpp"

class DebugLogging : public Logging {
 public:
  void print(const std::string& text) override;
};
