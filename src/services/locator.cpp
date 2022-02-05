#include "locator.hpp"

Logging& Locator::logging() { return logging_; }

#if DEBUG
DebugLogging Locator::logging_ = DebugLogging();
#else
ReleaseLogging Locator::logging_ = ReleaseLogging();
#endif