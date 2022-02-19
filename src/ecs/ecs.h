#pragma once

#include "ecs_interface.h"

class ECS : public ECSInterface {
 public:
  ECS();

  virtual void input() override;
  virtual void update() override;
  virtual void render(float delay) override;
};
