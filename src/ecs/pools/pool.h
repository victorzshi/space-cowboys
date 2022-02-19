#pragma once

class ECSInterface;

class Pool {
 public:
  Pool() {}
  virtual ~Pool() = default;
  Pool(const Pool& other) = default;

  virtual void initialize(ECSInterface& ecs, int total) = 0;

  virtual int begin() = 0;
  virtual int active() = 0;
  virtual int end() = 0;

  virtual void activate(ECSInterface& ecs, int id) = 0;
  virtual void deactivate(ECSInterface& ecs, int id) = 0;
};
