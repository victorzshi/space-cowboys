#pragma once

class Engine;

class Pool {
 public:
  Pool();
  virtual ~Pool() = default;
  Pool(const Pool& other) = default;

  virtual void initialize(Engine& e) = 0;

  int begin();
  int active();
  int end();

  void activate(Engine& e, int index);
  void deactivate(Engine& e, int index);

 protected:
  int begin_;
  int active_;
  int end_;

 private:
  static void swapMemory(Engine& e, int i, int j);
};
