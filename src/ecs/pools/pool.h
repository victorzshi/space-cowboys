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

  int begin();
  int active();
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
  int active_;
  int end_;

 private:
  void memorySwap(int index);
};
