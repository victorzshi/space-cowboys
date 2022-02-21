#pragma once

class Engine;

class UpdatePosition {
 public:
  static void update(Engine& e);

 private:
  static void updateAliensPath(Engine& e);
};
