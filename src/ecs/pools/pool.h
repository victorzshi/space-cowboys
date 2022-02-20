#pragma once

class Engine;
struct AI;
struct Collider;
struct Physics;
struct Sprite;
struct Transform;

class Pool {
 public:
  Pool();
  virtual ~Pool() = default;
  Pool(const Pool& other) = default;

  void setEngine(Engine* e);

  virtual void initialize() = 0;

  /*
      BEGIN    SIZE    END       pointers
        v       v       v
   ...  4   5   6   7   8  ...   array indexes
  | - | X | X | - | - | - | - |  contiguous array

  X = active data
  - = inactive data

  In this case, there are two active indexes at 4 and 5.
  Therefore the size of the pool is 2.
  However, to get the correct array index:

  SIZE = total active + array's first index
  SIZE = 2 + BEGIN
  SIZE = 2 + 4
  SIZE = 6
  */

  // Returns first valid index of the allocated array.
  int begin();
  // Returns current size plus offset.
  // Equivalent to first inactive index of the allocated array.
  // Since Pool keeps the array sorted:
  // 1. index < size are active
  // 2. index >= size are inactive
  int size();
  // Returns last valid index of the allocated array.
  int end();

  void activate(int index);
  void deactivate(int index);

 protected:
  Engine* e_;

  AI* ai_;
  Collider* collider_;
  Physics* physics_;
  Sprite* sprite_;
  Transform* transform_;

  int begin_;
  int size_;
  int end_;

 private:
  void memorySwap(int index);
};
