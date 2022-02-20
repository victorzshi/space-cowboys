#pragma once

class Engine;
class Pool;

class UpdatePosition {
 public:
  static void update(Engine& e);

 private:
  static void updateActive(Engine& e, Pool& pool);
  static void updateAliensPath(Engine& e);
  static void resolveBulletHit(Engine& e);
};
