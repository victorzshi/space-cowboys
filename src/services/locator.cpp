#include "locator.hpp"

Logging* Locator::getLogging() { return service_; }

void Locator::provide(Logging* service) { service_ = service; }

Logging* Locator::service_ = nullptr;
