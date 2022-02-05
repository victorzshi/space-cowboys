#include "../logging.hpp"

class NullLogging : public Logging {
 public:
  void print(const std::string& text) override;
};
