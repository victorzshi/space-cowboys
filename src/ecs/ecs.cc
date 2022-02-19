#include "ecs.h"

#include "services/locator.h"

ECS::ECS() {}

void ECS::input() { Locator::logger().print("Inputting..."); }

void ECS::update() { Locator::logger().print("Updating..."); }

void ECS::render(float delay) {
  (void)delay;
  Locator::logger().print("Rendering...");
}
