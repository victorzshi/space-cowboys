#include "locator.h"

#include "logger/debug_logger/debug_logger.h"
#include "logger/release_logger/release_logger.h"

void Locator::initialize() {
#ifdef DEBUG
  logger_ = new DebugLogger();
#else
  logger_ = new ReleaseLogger();
#endif
}

Logger& Locator::logger() { return *logger_; }

Logger* Locator::logger_ = nullptr;
