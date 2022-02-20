#pragma once

class Engine;
class Pool;

class RenderCollider {
 public:
  static void render(Engine& e);

 private:
  static void renderActive(Engine& e, Pool& pool);

  static void renderAllActive(Engine& e);
};
