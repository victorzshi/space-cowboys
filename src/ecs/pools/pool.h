#pragma once

class Engine;

class Pool {
 public:
  Pool() {}
  virtual ~Pool() = default;
  Pool(const Pool& other) = default;

  virtual void initialize(Engine& e, int total) = 0;

  virtual int begin() = 0;
  virtual int active() = 0;
  virtual int end() = 0;

  virtual void activate(Engine& e, int id) = 0;
  virtual void deactivate(Engine& e, int id) = 0;
};
