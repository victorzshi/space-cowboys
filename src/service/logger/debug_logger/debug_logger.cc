#include "debug_logger.h"

#include <iostream>

DebugLogger::DebugLogger() { std::cout << "DEBUG mode is ON..." << std::endl; }

void DebugLogger::print(const std::string& text) {
  std::cout << text << std::endl;
}