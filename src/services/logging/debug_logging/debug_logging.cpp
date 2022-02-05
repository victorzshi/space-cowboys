#include "debug_logging.hpp"

#include <iostream>

DebugLogging::DebugLogging() {
  std::cout << "DEBUG mode is ON..." << std::endl;
}

void DebugLogging::print(const std::string& text) {
  std::cout << text << std::endl;
}
