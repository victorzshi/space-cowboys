#include "locator.hpp"

Logger& Locator::logger() { return logger_; }

#if DEBUG
DebugLogger Locator::logger_ = DebugLogger();
#else
ReleaseLogger Locator::logger_ = ReleaseLogger();
#endif