#pragma once

#include "game_object/game_object.h"
#include "tank_input_component.h"
#include "tank_render_component.h"
#include "tank_update_component.h"

class Tank {
 public:
  static GameObject* createTank() {
    return new GameObject(new TankInputComponent(), new TankUpdateComponent(),
                          new TankRenderComponent());
  }
};
