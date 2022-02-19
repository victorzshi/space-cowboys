#pragma once

#include "ecs/engine.h"
#include "ecs/pools/pool.h"

class Bullets : public Pool {
 public:
  Bullets();

  virtual void initialize(Engine& e, int total) override;

  virtual int begin() override;
  virtual int active() override;
  virtual int end() override;

  virtual void activate(Engine& e, int id) override;

  virtual void deactivate(Engine& e, int id) override;

 private:
  int begin_;
  int active_;
  int end_;
};
