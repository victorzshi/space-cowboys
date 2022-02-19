#pragma once

#include "ecs/ecs_interface.h"
#include "ecs/pools/pool.h"

class Bullets : public Pool {
 public:
  Bullets();

  virtual void initialize(ECSInterface& ecs, int total) override;

  virtual int begin() override;
  virtual int active() override;
  virtual int end() override;

  virtual void activate(ECSInterface& ecs, int id) override;

  virtual void deactivate(ECSInterface& ecs, int id) override;

 private:
  int begin_;
  int active_;
  int end_;
};
