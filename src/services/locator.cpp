#include "locator.hpp"

void Locator::initialize() { 
  nullService_ = new NullLogging();
  service_ = nullService_; 
}

Logging& Locator::getLogging() { return *service_; }

void Locator::provide(Logging* service) {
  if (service == nullptr) {
    service = nullService_;
  }

  service_ = service;
}

Logging* Locator::service_ = nullptr;
NullLogging* Locator::nullService_ = nullptr;
