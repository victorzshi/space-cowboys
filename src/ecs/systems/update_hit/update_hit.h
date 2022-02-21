#pragma once

class Engine;

class UpdateHit {
 public:
  static void update(Engine& e);

 private:
  static void createExplosion(Engine& e, int index);
};
