#pragma once

#include "../logging.hpp"

class ReleaseLogging : public Logging {
 public:
  void print(const std::string& text) override;
};
