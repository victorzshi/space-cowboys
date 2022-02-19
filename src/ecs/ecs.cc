#include "ecs.h"

#include "services/locator.h"
#include "systems/process_input.h"

ECS::ECS() {}

void ECS::input() { ProcessInput::input(); }

void ECS::update() { 
  // Do nothing
}

void ECS::render(float delay) {
  // Do nothing
  (void)delay;
}
