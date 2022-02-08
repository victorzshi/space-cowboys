#pragma once

#include "game_object/game_object.h"
#include "tank_graphics_component.h"
#include "tank_input_component.h"
#include "tank_physics_component.h"

class Tank {
 public:
  static GameObject* createTank() {
    return new GameObject(new TankInputComponent(), new TankPhysicsComponent(),
                          new TankGraphicsComponent());
  }
};
