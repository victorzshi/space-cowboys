#include "locator.hpp"

#include "logger/debug_logger/debug_logger.hpp"
#include "logger/release_logger/release_logger.hpp"

void Locator::initialize() {
#if DEBUG
  logger_ = new DebugLogger();
#else
  logger_ = new ReleaseLogger();
#endif
}

Logger& Locator::logger() { return *logger_; }

Logger* Locator::logger_ = nullptr;
