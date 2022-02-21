#pragma once

class Engine;

class UpdateHit {
 public:
  static void update(Engine& e);

 private:
  static void updateBullets(Engine& e);
  static void updateZappers(Engine& e);
  static void explodeAlien(Engine& e, int index);
  static void explodeTank(Engine& e, int index);
};
