#pragma once

class Engine;

class UpdatePosition {
 public:
  static void update(Engine& e);

 private:
  static void updateAliens(Engine& e);
  static void updateBullets(Engine& e);
};
